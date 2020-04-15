/* ========================================
 *
 *
 *
 * ========================================
*/



enum bikeState 
{
    UNLOCKING=117,                      //ASCII u
    UNLOCKED_AND_ACTIVE=97,             //ASCII a
    UNLOCKED_AND_IDLE=105,              //ASCII i
    UNLOCKED_AND_IDLE_READY_TO_LOCK=114,//ASCII r
    LOCKED,
    LOCKING=108                         //ASCII l
};


enum SPItransmissionIdentifiers
{
    DATA_TRANSMISSION = 100,             //ASCII d
    
    EVENT_TRANSMISSION = 101,            //ASCII e
};



/**************Enums for indexing txBuffer***************/
enum dataTXindex
{
    MESSAGE_TYPE_ID_INDEX = 0,
    SPEED_INDEX = 1,
    DISTANCE_INDEX = 2,
    MOVEMENT_INDEX = 3
};

enum eventTXindex
{
    //messageTypeIdentifierIndex = 0,
    FIRST_EVENT_INDEX = 1,
    SECOND_EVENT_INDEX = 2,
    THIRD_EVENT_INDEX = 3,
};


/**************Enums for commands from master***************/
enum masterCommands
{
    LOCK_COMMAND=76,        //ASCII L
    UNLOCK_COMMAND=85,      //ASCII U
    SET_WHEEL_CIRC=87       //ASCII W
};

enum commandRXindex
{
    COMMAND_INDEX=0,
    FIRST_CMD_DATA_INDEX=1,
    SECOND_CMD_DATA_INDEX=2,
    THIRD_CMD_DATA_INDEX=3
};


/* [] END OF FILE */
