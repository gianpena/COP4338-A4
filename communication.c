/* 
   ####################################################
   IMPLEMENT FUNCTION 3:
    - add_communication() (20 points)
   ################################################### 
*/


#include "space_mission.h"

/**
 * FUNCTION 3: add_communication 
 * 
 * PURPOSE: Add a communication log entry to a specified mission
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   mission_id - Target mission identifier
 *   timestamp - Communication timestamp in YYYY-MM-DD HH:MM format
 *   priority - Message priority (ROUTINE, URGENT, or EMERGENCY)
 *   message - Communication message content
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Validate all parameters: input parameters, enum values, NULL checks, timestamp format using `is_valid_timestamp_format()`
 *  - Validate MessagePriority enum values (ROUTINE, URGENT, EMERGENCY)
 *  - Find target mission by mission_id, return -1 if not found
 *  - Expand communications array using realloc when needed (double capacity)
 *  - Generate unique log_id and initialize communication structure
 */
int add_communication(MissionControl* system, int mission_id, const char* timestamp,
                     MessagePriority priority, const char* message) {
       
   // step 1
   if(system == NULL) return -1;
   if(timestamp == NULL) return -1;
   if(message == NULL) return -1;
   if(!(message[0] != '\0' && strlen(message) <= MAX_MESSAGE_LENGTH)) return -1;
   if(!is_valid_timestamp_format(timestamp)) return -1;
   
   if(!(priority == ROUTINE || priority == URGENT || priority == EMERGENCY)) return -1;

   // step 2
   Mission *missions = system->missions;
   int bound = system->capacity < system->mission_count ? system->capacity : system->mission_count;
   int i=0;
   for(;i < bound && (missions[i].mission_id != mission_id); ++i);
   if(i >= bound) return -1;

   // step 3
   if(missions[i].comm_count >= missions[i].comm_capacity) {
      int new_capacity = missions[i].comm_capacity << 1;
      missions[i].communications = (CommLog *) realloc(missions[i].communications, sizeof(CommLog) * new_capacity);
      if(missions[i].communications == NULL) return -1;
      missions[i].comm_capacity = new_capacity;
   }

   // step 4
   int old_count = missions[i].comm_count;
   int new_log_id = old_count + 1;
   CommLog *comms = missions[i].communications;
   comms[old_count].log_id = new_log_id;
   strcpy(comms[old_count].timestamp, timestamp);
   comms[old_count].priority = priority;
   strcpy(comms[old_count].message, message);
   comms[old_count].acknowledged = 0;
   missions[i].comm_count = old_count + 1;

   return 0;
    
}