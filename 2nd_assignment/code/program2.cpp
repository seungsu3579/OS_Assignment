#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[]) {

    int total_process_num;          //프로세스 개수
    int status;                     //fork된 프로세스 상태 저장
    int numFilter;                  //적용될 필터의 개수
    int xFilter;                    //적용될 필터의 세로크기
    int yFilter;                    //적용될 필터의 가로크기
    int xImage;                     //주어진 이미지의 세로크기
    int yImage;                     //주어진 이미지의 가로크기
    int xResult;                    //합성곱 결과 이미지의 세로크기
    int yResult;                    //합성곱 결과 이미지의 가로크기
    int* filter_partitions;         //프로세스 별 담당할 필터 수를 담을 배열

    struct timeval start,end;       //시간 측정을 위한 시작지점, 종료지점
    long* process_time_ms;          //자식 프로세스의 수행시간을 담을 배열
    long total_time_ms;             //부모 프로세스의 수행시간(총 시간)

    // 프로세스 개수
    total_process_num = atoi(argv[1]);

    // 필터 정보 입력
    scanf("%d", &numFilter);
    scanf("%d", &xFilter);
    scanf("%d", &yFilter);

    // 프로세스별 담당할 필터 수 계산
    int share = numFilter / total_process_num;
    int remainder = numFilter % total_process_num;
    int stack_filter_num = 0;
    filter_partitions = new int[total_process_num + 1];
    for(int k = 0 ; k < total_process_num ; k++){
        filter_partitions[k] = stack_filter_num;
        if(k < remainder && remainder != 0){
            stack_filter_num += share + 1;
        }else{
            stack_filter_num += share;
        }
    }
    filter_partitions[total_process_num] = numFilter;


    //각각의 자식 프로세스가 받을 표준입력파일 생성
    FILE* files[total_process_num];
    for(int p = 0 ; p < total_process_num ; p++){
        //각 자식 프로세스가 표준입력으로 받을 inputPs.txt을 쓰기 모드로 생성
        char filename[20];
        sprintf(filename, "inputPs%d.txt", p);
        files[p] = fopen(filename, "w");
        // 각 자식 프로세스가 계산할 필터 정보 입력
        fprintf(files[p], "%d %d %d ", (filter_partitions[p+1] - filter_partitions[p]), xFilter, yFilter);

        // 각 자식 프로세스가 수행할 필터 정보를 표준입력에서 불러와 각각의 inputPs.txt에 저장
        int filterSize = (filter_partitions[p+1] - filter_partitions[p]) * xFilter * yFilter * 3;
        for(int k = 0 ; k < filterSize ; k++){
            int num;
            scanf("%d", &num);
            fprintf(files[p], "%d ", num);
        }
    }


    // 이미지 정보 입력
    scanf("%d", &xImage);
    scanf("%d", &yImage);

    // 각 자식 프로세스가 받을 표준입력파일에 이미지 크기 정보 입력
    for(int p = 0 ; p < total_process_num ; p++){
        fprintf(files[p], "%d %d ", xImage, yImage);
    }

    // 각 자식 프로세스가 받을 표준입력파일에 이미지 정보 입력
    int imageSize = xImage * yImage * 3;
    for(int k = 0 ; k < imageSize ; k++){
        int num;
        scanf("%d", &num);
        for(int p = 0 ; p < total_process_num ; p++){
            fprintf(files[p], "%d ", num);
        }
    }
    fcloseall();            //파일 닫기


    // 합성곱 결과 이미지 크기 계산
    xResult = xImage - xFilter + 3;
    yResult = yImage - yFilter + 3;

    // 부모 프로세스 시간 측정 시작
    gettimeofday(&start, NULL);


    // 총 프로세스 수 만큼 프로세스 생성(fork)
    pid_t pidList[total_process_num];
    FILE* outFiles[total_process_num];
    for(int p = 0 ; p < total_process_num ; p++){
        // 각 자식 프로세스의 표준 출력을 받을 outputPs.txt파일 생성
        char outputText[20];
        sprintf(outputText, "outputPs%d.txt", p);
        outFiles[p] = fopen(outputText, "w");
        // 자식 프로세스 생성
        pidList[p] = fork();

        // 자식 프로세스 생성 실패
        if(pidList[p] < 0){
            perror("FORK FAIL");
            exit(EXIT_FAILURE);

        // 자식 프로세스
        }else if(pidList[p] == 0){
            int in, out;
            char* args[] = {"./program1", NULL};
            char inputText[20];
            sprintf(inputText, "inputPs%d.txt", p);

            // redirection을 위한 파일 디스크립터
            in = open(inputText, O_RDONLY);
            out = open(outputText, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

            // 사전에 지정한 파일 디스크립터를 자식 프로세스의 표준입출력에 redirection
            dup2(in, 0);
            dup2(out, 1);

            // program1 호출
            execvp("./program1", args);

            // program1 종료
            exit(EXIT_SUCCESS);

        // 부모 프로세스
        }else{
        }

    }

    // 부모 프로세스가 모든 자식 프로세스 종료를 wait
    for(int p = 0 ; p < total_process_num ; p++){
        waitpid(pidList[p], &status, WUNTRACED);
    }

    // 부모 프로세스 시간 측정 종료
    gettimeofday(&end, NULL);
    total_time_ms = ((long)end.tv_sec - (long)start.tv_sec)*1000 + ((long)end.tv_usec - (long)start.tv_usec)/1000;

    process_time_ms = new long[total_process_num];      //자식 프로세스의 수행시간을 담을 배열

    // 각 자식프로세스 표준출력을 받아와 출력
    for(int p = 0 ; p < total_process_num ; p++){
        char outputText[20];
        sprintf(outputText, "outputPs%d.txt", p);
        outFiles[p] = fopen(outputText, "r");
        for(int f = 0 ; f < filter_partitions[p+1] - filter_partitions[p] ; f++){
            for(int j = 0 ; j < xResult ; j++){
                for(int i = 0 ; i < yResult ; i++){
                    int num;
                    fscanf(outFiles[p], "%d", &num);
                    printf("%d ", num);
                }
                printf("\n");
            }
            printf("\n");
        }

        // 자식 프로세스의 수행 시간은 출력하지 않고 배열에 저장
        long time;
        fscanf(outFiles[p], "%ld", &time);
        process_time_ms[p] = time;
	fcloseall();
    }

    // 자식 프로세스의 표준입출력 파일을 삭제
    system("rm -rf inputPs*");
    system("rm -rf outputPs*");

    // 자식 프로세스의 수행시간 출력
    for(int p = 0 ; p < total_process_num ; p++){
        printf("%ld ", process_time_ms[p]);
    }
    // 부모 프로세스의 수행시간 출력
    printf("\n%ld\n", total_time_ms);

    // 프로그램 종료
    return 0;
}
