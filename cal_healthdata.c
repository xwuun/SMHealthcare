//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
	int total_cal_burn, total_cal_intake;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for(i=0; i<health_data->exercise_count; i++)
    {
    	// 운동이름, 분당 칼로리 소모량을 저장한다. 
        fprintf(file,"%s - %d kcal\n",health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
        //총 소모된 칼로리 계산하기  
		total_cal_burn += health_data->exercises[i].calories_burned_per_minute;
    }
	fprintf(file, "Total calories burned: %d kcal\n", total_cal_burn);    
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n");
    for(i=0;i<health_data->diet_count;i++)
    {
    	//음식이름, 섭취 칼로리를 저장한다. 
        fprintf(file,"%s - %d kcal\n",health_data->diet[i].food_name, health_data->diet[i].calories_intake);
        //총 섭취한 칼로리 계산하기 
		total_cal_intake += health_data->diet[i].calories_intake;
    }
    fprintf(file, "Total calories intake: %d kcal\n", total_cal_intake);

    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    fprintf(file,"Basal metabolic rate - %d kcal\n",BASAL_METABOLIC_RATE); // 기초 대사량을 저장 
    fprintf(file,"The remaining calories - %d kcal\n",getRemainCal(health_data)); // 남은 칼로리 저장 

    fclose(file);
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void recommendation_msg(const HealthData* health_data);

void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
    for(i=0;i<health_data->exercise_count;i++) // 저장되어있는 모든 운동정보들을 출력함. 
    {
        printf("Exercise %s, Calories burned : %d kcal\n",health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
    }
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for(i=0;i<health_data->diet_count;i++) //저장되어있는 모든 식당정보들을 출력. 
    {
        printf("Food %s, Calories intake: %d kcal\n",health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    }

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    printf("Basal Metabolic Rate : %d \n",BASAL_METABOLIC_RATE);
    printf("Total calories burned : %d \n", health_data->total_calories_burned );
    printf("Total calories intake : %d \n", health_data->total_calories_intake );
    printf("Total remaining calories: %d kcal\n",getRemainCal(health_data));
    
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    
    recommendation_msg(health_data);
	printf("=======================================================================\n");
}

/*
    description : 잔여 칼로리를 계산하는 함수
*/
int getRemainCal(const HealthData* health_data)
{
	// 잔여 칼로리 = 총 섭취칼로리 - 총 소모 칼로리 - 기초대사량 
    int calorie=health_data->total_calories_intake - 
                health_data->total_calories_burned - BASAL_METABOLIC_RATE;

    return calorie; //계산한 잔여 칼로리를 반환 
}

/*
    description : 사용자에게 추천사항을 출력하는 함수
*/

void recommendation_msg(const HealthData* health_data)
{   
    printf("[ Recommendtaion Message ] \n");
    if(getRemainCal(health_data)<0) // 잔여 칼로리가 0보다 작은 경우 
    {
        printf("[Warning] Too few calories!!\n");
        if(health_data->total_calories_intake == BASAL_METABOLIC_RATE) // 섭취한 칼로리가 기초대사량과 동일한 경우 
        {
            printf(" *  Your total calories intake for today has reached your goal!\n");
        }
        else if(health_data->total_calories_intake < BASAL_METABOLIC_RATE) // 섭취 칼로리가 기초대사량 보다 작은 경우 
        {
            printf("Your total calories intake for today has not reached your goal,\n");
            printf("remember to eat more!!\n");
        }
        else{
        	//칼로리 섭취가 초과되었으나 운동으로 인해  칼로리가 부족한 경우 
            printf("You have eaten more calories than planned today,\n");  
            printf("but you have exercised too much!!\n");
        }
    }
    else{ 
    //잔여  칼로리가 0이상인 경우 
        if(health_data->total_calories_intake == BASAL_METABOLIC_RATE) // 섭취한 칼로리가 기초대사량과 동일한 경우 
        {
            printf("Your total calories intake for today has reached your goal!\n");
        }
        else if(health_data->total_calories_intake < BASAL_METABOLIC_RATE) // 섭취한 칼로리가 기초대사량 보다 작은 경우 
        {
            printf("Your total calories intake for today has not reached your goal,\n");
            printf("remember to eat more!!\n");
        }
    }
}
