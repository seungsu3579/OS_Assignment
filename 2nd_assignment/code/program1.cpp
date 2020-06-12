#include <iostream>
#include <sys/time.h>
#include <unistd.h>


using namespace std;

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
    int** convolution(){
        int** oneChannel = new int*[x];
        for(int j = 0 ; j < x ; j++){
            oneChannel[j] = new int[y];
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

int main(int argc, char* argv[]) {
    int numFilter;                  //적용될 필터의 개수
    int xFilter;                    //적용될 필터의 세로크기
    int yFilter;                    //적용될 필터의 가로크기
    int xImage;                     //주어진 이미지의 세로크기
    int yImage;                     //주어진 이미지의 가로크기

    long total_time_ms;             //총 시간 측정
    struct timeval start,end;       //시간측정을 위한 시작지점, 종료지점

    // 필터 정보 입력
    scanf("%d", &numFilter);    
    scanf("%d", &xFilter);
    scanf("%d", &yFilter);

    Image* filters = new Image[numFilter];  //필터 관리를 위해 배열을 생성
    for(int n = 0 ; n < numFilter ; n++){
        Image filter = Image(xFilter, yFilter);
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


    // 합성곱 결과 이미지 크기 계산
    int xResult = xImage - xFilter + 3;
    int yResult = yImage - yFilter + 3;

    // 합성곱 연산과 활성화함수가 적용된 2차원 배열을 담을 배열 생성
    int*** answerArray = new int**[numFilter];

    // 합성곱 연산 결과를 담은 이미지 객체를 저장할 배열 생성
    Image* cnnImage = new Image[numFilter];
    
    // 시간 측정 시작
    gettimeofday(&start, NULL);

    
    // 필터별 합성곱 연산
    for(int f = 0 ; f < numFilter ; f++){
        cnnImage[f] = *(new Image(xResult, yResult));

        // n : 채널
        for(int n = 0 ; n < 3 ; n++){
            // j : 세로축
            for(int j = 0 ; j < xResult ; j++){
                // i : 가로축
                for(int i = 0 ; i < yResult ; i++){
                    //필터 적용 : n채널 j,i에 필터를 적용한 값 계산
                    int sum = 0;
                    for(int a = 0 ; a < xFilter ; a++){
                        for(int b = 0 ; b < yFilter ; b++){
                            sum += filters[f].channels[n][a][b] * originImage.channels[n][j + a][i + b];
                        }
                    }
                    cnnImage[f].channels[n][j][i] = sum;
                }
            }
        }
    }

    // 합성곱 연산의 결과를 차원을 1차원으로 줄이고 Relu 적용
    for(int f = 0 ; f < numFilter ; f++){
        answerArray[f] = cnnImage[f].convolution();
    }

    // 시간 측정 종료
    gettimeofday(&end, NULL);
    total_time_ms = ((long)end.tv_sec - (long)start.tv_sec)*1000 + ((long)end.tv_usec - (long)start.tv_usec)/1000;

    // 결과 출력
    for(int f = 0 ; f < numFilter ; f++){
        for(int j = 0 ; j < xResult ; j++){
            for(int i = 0 ; i < yResult ; i++){
                printf("%d ", answerArray[f][j][i]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // 시간 출력
    printf("%ld\n", total_time_ms);

    // 프로그램 종료
    return 0;
}
