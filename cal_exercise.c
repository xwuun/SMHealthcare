//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES]; //운동 관련 정보를 가지는 database 생성 
int exercise_list_size = 0; //운동 리스트 크기 


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    char line[100]; //파일에서 읽어온 글자를 저장할 배열 
    FILE *file = fopen(EXERCISEFILEPATH,"r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fgets(line,sizeof(line), file)) {
        sscanf(line,"%s %d",exercise_list[exercise_list_size].exercise_name, //운동이름 
                            &exercise_list[exercise_list_size].calories_burned_per_minute); //시간당 소모한 칼로리 저장 
        exercise_list_size++; //운동 리스트 크기 증가 
        //최대 개수에 도달하면 읽기를 중단한다
        if (exercise_list_size >= MAX_EXERCISES) break;
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");

    // ToCode: to enter the exercise to be chosen with exit option
    for(i=0; i<exercise_list_size; i++)
    {
    	//운동 이름, 분당 칼로리 소모량을 출력한다. 
        printf("%d : %s - %d kcal per min.\n",i,exercise_list[i].exercise_name,exercise_list[i].calories_burned_per_minute);
    }
    
    // 유효한 diet code를 입력할 때 까지 반복한다.
    while(1)
    {
        printf("\nPlease input Exercise code : ");
        scanf("%d",&choice);
        if (choice<0||choice>=exercise_list_size) //유효하지 번호를 입력하였을 때 에러 메세지 출력한다. 
        {
            printf("Exercise code Error!!\n");
        } 
        else{
            break;
        }
    }
    // To enter the duration of the exercise
    printf("\nEnter the duration of the exercise (in min.): ");
    scanf("%d", &duration); //입력받은 시간을 변수 duration에 저장한다. 
    int burned_cal=duration*exercise_list[choice].calories_burned_per_minute; //소모한 칼로리를 계산 

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    // 선택한 운동 정보를 health_data에 추가
    strcpy( health_data->exercises[health_data->exercise_count].exercise_name, 
            exercise_list[choice].exercise_name);
    health_data->exercises[health_data->exercise_count].calories_burned_per_minute = burned_cal;
    // 소모한 칼로리를 계산하고 누적한다. 
    health_data->total_calories_burned+=burned_cal;
    health_data->exercise_count++;

}
