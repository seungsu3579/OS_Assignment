#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mutex>


using namespace std;

mutex sync;                  // 동기화를 위한 mutex 생성

//필터와 이미지를 저장할 Image클래스 정의
class Image{

public:
    int x;
    int y;
    int** channel1;
    int** channel2;
    int** channel3;
    int*** channels;

    //Image 클래스는 가로, 세로 크기와 3채널의 2차원 배열을 가지고 있다.
    Image(int xInput, int yInput){
        x = xInput;
        y = yInput;
        channel1 = new int*[x];
        channel2 = new int*[x];
        channel3 = new int*[x];
        channels = new int**[3] { channel1, channel2, channel3 };
        for(int n = 0; n < 3; n++){
            for(int j = 0; j < x; j++) {
                channels[n][j] = new int[y]();
            }
        }
    }

    Image(){
    }

    //표준입력을 받아 이미지를 구축하는 메서드
    void setData(){
        for(int n = 0; n < 3; n++){
            for(int j = 0; j < x; j++) {
                channels[n][j] = new int[y];
                for (int i = 0; i < y; i++) {
                    scanf("%d", &channels[n][j][i]);
                }
            }
        }
    }

    //Image객체에 가로 세로 0 padding을 하나씩 추가해주는 메서드
    void padding(){
        int** newChannel1 = new int*[x+2];
        int** newChannel2 = new int*[x+2];
        int** newChannel3 = new int*[x+2];
        int*** newChannels = new int**[3] { newChannel1, newChannel2, newChannel3 };

        for(int n = 0 ; n < 3 ; n++){
            for(int j = 0 ; j < x + 2; j++){
                //배열 0초기화
                newChannels[n][j] = new int[y + 2]();
            }
        }

        for(int n = 0 ; n < 3 ; n++){
            for(int j = 0 ; j < x ; j++){
                for(int i = 0; i < y ; i++){
                    newChannels[n][j+1][i+1] = channels[n][j][i];
                }
            }
        }

        channels = newChannels;
        channel1 = newChannel1;
        channel2 = newChannel2;
        channel3 = newChannel3;

        x += 2;
        y += 2;
    }

    //3개의 채널을 하나로 축소하고 Relu 활성화함수를 적용한 2차원 배열을 리턴하는 메서드
    int** convolution(int** oneChannel){
        for(int j = 0 ; j < x ; j++){
            for(int i = 0 ; i < y ; i++){
                //채널 축소
                int sum = channel1[j][i] + channel2[j][i] + channel3[j][i];
                //Relu 활성화함수
                if (sum <= 0){
                    oneChannel[j][i] = 0;
                }else{
                    oneChannel[j][i] = sum;
                }
            }
        }
        return oneChannel;
    }
};

// 스레드함수에 여러 인자를 넘겨주기 위한 구조체 정의
struct MultipleArgs{
    int numFilter;                  //적용될 필터의 개수
    int xImage;                     //주어진 이미지의 세로크기
    int yImage;                      //주어진 이미지의 가로크기
    int xFilter;                    //적용될 필터의 세로크기
    int yFilter;                    //적용될 필터의 가로크기

    int th_num;                     //몇번째 스레드인지
    int* filter_partitions;         //스레드 별 필터 정보
    long* thread_times_ms;          //스레드 별 수행시간을 담을 배열

    Image* filters;                 //필터 정보
    Image originImage;              //이미지 정보

    int*** sub_answers;             //출력 결과를 담을 2차원 배열의 배열
};

//스레드 함수 : 수행시간 계산, 합성곱 및 차원축소, Relu를 적용
void *calcImageThread(void* arg){
    struct timeval start_th, end_th;    //시간측정을 위한 시작지점, 종료지점
    // 스레드 시간 측정 시작
    gettimeofday(&start_th, NULL);

    // 다중인자
    MultipleArgs *args = (MultipleArgs *)arg;

    // 합성곱 결과 이미지 크기 계산
    int xResult = args->xImage - args->xFilter + 3;
    int yResult = args->yImage - args->yFilter + 3;

    // 합성곱 결과 이미지를 담을 이미지 배열 생성
    Image* cnnImage = new Image[args->numFilter];


    // 스레드 별 담당할 필터만 적용하여 합성곱 연산
    for(int f = args->filter_partitions[args->th_num] ; f < args->filter_partitions[args->th_num + 1] ; f++){
        cnnImage[f] = *new Image(xResult, yResult);
        // n : 채널
        for(int n = 0 ; n < 3 ; n++){
            // j : 세로축
            for(int j = 0 ; j < xResult ; j++){
                // i : 가로축
                for(int i = 0 ; i < yResult ; i++){
                    //필터 적용 : n채널 j,i에 필터를 적용한 값 계산
                    int sum = 0;
                    for(int a = 0 ; a < args->xFilter ; a++){
                        for(int b = 0 ; b < args->yFilter ; b++){
                            sum += args->filters[f].channels[n][a][b] * args->originImage.channels[n][j + a][i + b];
                        }
                    }
                    cnnImage[f].channels[n][j][i] = sum;
                }
            }
        }
    }

    // 합성곱 연산의 결과를 차원을 1차원으로 줄이고 Relu 적용 
    // 사전에 할당해놓은 힙메모리에 저장
    for(int f = args->filter_partitions[args->th_num] ; f < args->filter_partitions[args->th_num + 1] ; f++){
        sync.lock();        // mutex lock 
        args->sub_answers[f] = cnnImage[f].convolution(args->sub_answers[f]);
        sync.unlock();      // mutex unlock
    }

    // 스레드 시간 측정 종료
    gettimeofday(&end_th, NULL);
    args->thread_times_ms[args->th_num] = ((long)end_th.tv_sec - (long)start_th.tv_sec)*1000 + ((long)end_th.tv_usec - (long)start_th.tv_usec)/1000;
    
    // 스레드 종료
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    int numFilter;                  //적용될 필터의 개수
    int xFilter;                    //적용될 필터의 세로크기
    int yFilter;                    //적용될 필터의 가로크기
    int xImage;                     //주어진 이미지의 세로크기
    int yImage;                     //주어진 이미지의 가로크기
    int total_thread_num;           //스레드 개수
    int status;                     //각 스레드 상태 저장
    int* filter_partitions;         //스레드 별 담당할 필터 수를 담을 배열
    long total_time_ms;             //부모 프로세스의 수행시간(총 시간)
    long* thread_times_ms;          //스레드별 수행시간을 담을 배열

    struct timeval start,end;       //시간 측정을 위한 시작지점, 종료지점


    // 필터 정보 입력
    scanf("%d", &numFilter);
    scanf("%d", &xFilter);
    scanf("%d", &yFilter);

    Image* filters = new Image[numFilter];
    for(int n = 0 ; n < numFilter ; n++){
        Image filter = *(new Image(xFilter, yFilter));
        filter.setData();
        filters[n] = filter;
    }

    // 이미지 정보 입력
    scanf("%d", &xImage);
    scanf("%d", &yImage);

    Image originImage = Image(xImage, yImage);
    originImage.setData();

    // 이미지 0 padding
    originImage.padding();


    // 스레드 개수
    total_thread_num = atoi(argv[1]);

    // 스레드별 담당할 필터 수 계산
    int share = numFilter / total_thread_num;
    int remainder = numFilter % total_thread_num;
    int stack_filter_num = 0;
    filter_partitions = new int[total_thread_num + 1];
    for(int k = 0 ; k < total_thread_num ; k++){
        filter_partitions[k] = stack_filter_num;
        if(k < remainder && remainder != 0){
            stack_filter_num += share + 1;
        }else{
            stack_filter_num += share;
        }
    }
    filter_partitions[total_thread_num] = numFilter;


    // 합성곱 결과 이미지 크기 계산
    int xResult = xImage - xFilter + 3;
    int yResult = yImage - yFilter + 3;

    // 출력결과를 담을 2차원 배열의 배열을 힙메모리에 올림
    int*** sub_answers = new int**[numFilter];
    for (int f = 0; f < numFilter; ++f) {
        sub_answers[f] = new int*[xResult];
        for(int j = 0 ; j < xResult ; j++){
            sub_answers[f][j] = new int[yResult];
        }
    }


    // 시간 측정 시작
    gettimeofday(&start, NULL);


    // 총 스레드 수 만큼 스레드 생성(pthread_create)
    pthread_t pthread[total_thread_num];
    thread_times_ms = new long[total_thread_num];
    for(int th = 0 ; th < total_thread_num ; th++){

        // 스레드 함수에 전달할 데이터를 담은 구조체 생성
        MultipleArgs *multipleArgs;
        multipleArgs = new MultipleArgs();
        multipleArgs->numFilter = numFilter;
        multipleArgs->xImage=xImage;
        multipleArgs->yImage=yImage;
        multipleArgs->xFilter=xFilter;
        multipleArgs->yFilter=yFilter;
        multipleArgs->filters=filters;
        multipleArgs->originImage=originImage;
        multipleArgs->th_num=th;
        multipleArgs->filter_partitions=filter_partitions;
        multipleArgs->sub_answers=sub_answers;
        multipleArgs->thread_times_ms=thread_times_ms;

        // 스레드 생성 > calcImageThread를 실행
        int th_id = pthread_create(&pthread[th], NULL, calcImageThread, (void *)multipleArgs);
        // 스레드 생성 실패
        if(th_id < 0){
            perror("FAIL THREAD CREATE");
            exit(0);
        }
    }

    // 부모프로세스가 모든 스레드 종료를 wait
    for(int i = 0 ; i < total_thread_num ; i++){
        pthread_join(pthread[i], (void **)&status);
    }


    // 시간 측정 종료
    gettimeofday(&end, NULL);
    total_time_ms = ((long)end.tv_sec - (long)start.tv_sec)*1000 + ((long)end.tv_usec - (long)start.tv_usec)/1000;

    // sub_answers에 담긴 출력결과 출력
    for(int f = 0 ; f < numFilter ; f++){
        for(int j = 0 ; j < xResult ; j++){
            for(int i = 0 ; i < yResult ; i++){
                printf("%d ", sub_answers[f][j][i]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // 스레드별 수행시간 출력
    for(int p = 0 ; p < total_thread_num ; p++){
        printf("%ld ", thread_times_ms[p]);
    }

    // 부모프로세스의 수행시간 출력
    printf("\n%ld\n", total_time_ms);

    // 프로그램 종료
    return 0;
}
