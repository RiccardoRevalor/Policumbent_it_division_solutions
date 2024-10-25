/* Includes ------------------------------------------------------------------*/
#include "app_gnss.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo.h"



/* Private variables ---------------------------------------------------------*/
static GNSSParser_Data_t GNSSParser_Data;



/* USER CODE BEGIN PV */    //Insert code if necessary

//BONUS QUESTION: Implement a circular queue as an First-Class ADT through
//importing queue.h
#include "queue.h"

/* USER CODE END PV */




/* Private Functions ---------------------------------------------------------*/



/**	
 * @brief  This function must return a random integer between 0 and the maximum value for an 8-bit integer unsigned (Big Endian representation)
 * @retval an 8-bit integer unsigned value in a 32-bit integer unsigned variable.
 */
static uint32_t getValue() {
    
    /* USER CODE BEGIN 1 */     //Insert code if necessary

    //max value for an 8-bit integer unsigned
    //rand() % (max_number + 1 - minimum_number) + minimum_number
    //rand() % (255 + 1 - 0) + 0

    //rand() returns 32 bit integers. 
    //Since the function returns a 32 bit integer, the return value is stored in a 32 bit integer variable.
    //the last 8 bits of the 32 bit integer variable are the random number between 0 and 255.
    return (rand() % 256); 
    
    
    /* USER CODE END 1 */

}



/**	
 * @brief  This function must check with bit wise operation the content of the variable value and perform
 * the corrispondent actions described in the README.md
 * @param  args generic arguments
 */

void task(void *args){

    uint32_t value;

    /* USER CODE BEGIN 1 */     //Insert code if necessary

    /* USER CODE END 1 */

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN 2 */     //Insert code if necessary

    //GNSSParser_Data initialization
    if GNSS_PARSER_Init(&GNSSParser_Data) != GNSS_PARSER_OK {
        //ERROR: GNSSParser_Data initialization failed
        printf("ERROR: GNSSParser_Data initialization failed\n");
        return -1;
    }

    //initialize 3 circular queue of size 10 each for storing GPGGA, GNS and GPRMC messages
    Queue *GPGGA_queue = createQueue(10);
    Queue *GNS_queue = createQueue(10);
    Queue *GPRMC_queue = createQueue(10);

    /* Initialization of the Parser*/

    /* USER CODE END 2 */

    while(1){

        value = getValue();
        /* USER CODE BEGIN WHILE */     //Insert code if necessary

        //Assuming a Little Endian representation, the bitwise operation is performed to the LSB down to the MSB
        if (value & (1 << 2)) {  // Third bit -> GPGGA
            GNSS_PARSER_ParseMsg(&GNSSParser_Data, GPGGA); //analysis of the message
            GNSS_PARSER_Print(&GNSSParser_Data, GPGGA); //print the message

            //store the msg in the corresponding queue
            if (!enqueue(GPGGA_queue, (void *) &GNSSParser_Data.gpgga_data)) {
                //ERROR: the queue is full
                printf("ERROR: the GPGGA queue is full\n");
            }
        } else if (value & (1 << 1)) {  // Second bit -> GNS
            GNSS_PARSER_ParseMsg(&GNSSParser_Data, GNS);
            GNSS_PARSER_Print(&GNSSParser_Data, GNS);

            //store the msg in the corresponding queue
            if (!enqueue(GNS_queue, (void *) &GNSSParser_Data.gns_data)) {
                //ERROR: the queue is full
                printf("ERROR: the GNS queue is full\n");
            }
        } else if (value & (1 << 0)) {  // First bit -> GPRMC
            GNSS_PARSER_ParseMsg(&GNSSParser_Data, GPRMC);
            GNSS_PARSER_Print(&GNSSParser_Data, GPRMC);

            //store the msg in the corresponding queue
            if (!enqueue(GPRMC_queue, (void *) &GNSSParser_Data.gprmc_data)) {
                //ERROR: the queue is full
                printf("ERROR: the GPRMC queue is full\n");
            }
        }

        /* USER CODE END WHILE */


        HAL_Delay(500); /* Delay of 500 ms */
    }
}

/* USER CODE BEGIN PF */     //Insert code if necessary

//free the queues
freeQueue(GPGGA_queue);
freeQueue(GNS_queue);
freeQueue(GPRMC_queue);

/* USER CODE END PF */