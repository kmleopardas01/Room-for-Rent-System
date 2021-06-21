#define MAX_LEN 128
typedef struct tenant{ //structure using both structure tag and synonym
	char first_name[100];//stores first name
	char last_name[100];//stores last name
	char cp_number[20];//stores contact number
	char unit_occupied[100]; //stores the name of the unit occupied
	struct tenant *next_tenant;//pointer to the next tenant in the list
}tenant;//synonym
typedef struct unit{//structure using both structure tag and synonym
	char unit_name[100];//stores the unit name
	int unit_id;
	int max_occupant;//stores the number of max occupants allowed
	int number_of_occupants;//counter for the current number of occupants
	tenant *tenants;//pointer to the structure of tenants

	struct unit *next_unit;//pointer to the next unit in the list
}unit;//synonym
 //prints the welcome sign 
void print_image(FILE *fptr){
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL){
    printf("%s",read_string);
    }
    printf("\n");        
}
//function to print the menu
int printMenu(){
	int choice;
	printf("\t\t\t+--------------------------------------------------+\n");
	printf("\t\t\t+     1. Add Unit                                  +\n");
	printf("\t\t\t+     2. Add Tenant                                +\n");
	printf("\t\t\t+     3. Search Tenant                             +\n");
	printf("\t\t\t+     4. Move Tenant                               +\n");
	printf("\t\t\t+     5. Remove Tenant                             +\n");
	printf("\t\t\t+     6. Edit Tenant                               +\n");
	printf("\t\t\t+     7. Print Master List of Occupants            +\n");
	printf("\t\t\t+     8. Print List of Occupants per Unit          +\n");
	printf("\t\t\t+     9. Remove Unit                               +\n");
	printf("\t\t\t+     10. Exit                                     +\n");
	printf("\t\t\t+--------------------------------------------------+\n");
	printf("\tChoice:");
	printf("\t");
	scanf("%d", &choice); //asks for user's choice
	printf("\n");

	return choice;//return choice to the main function
}
//function to transform all strings that will be inputted into uppercase
//to disregard case sensitivity
void Transform_to_Upper(char *string){
	int i;
	for(i = 0; i<strlen(&(*string)); i++){//iterating each character of the string
		(string[i]) = toupper(string[i]);//using the toupper() function
	}
}
//function to add units (first unit)
void Add_Unit(unit **unit_head, int *counter,int*unit_counter){
	printf("\t\t\t\tEnter name of unit: ");
	getchar();//gets the \n inputted by the user
	scanf("%[^\n]s",(*unit_head)->unit_name);//asks for the unit name
	Transform_to_Upper((*unit_head)->unit_name);//makes the name uppercase
	printf("\t\t\t\tEnter maximum number of occupants: ");
	scanf("%d", &((*unit_head)->max_occupant));//asks for the max occupant in the unit
	(*unit_head)->unit_id = (*counter);//assigns the counter as the id of the unit
	(*unit_head)->number_of_occupants = 0; //initiliazing number of occupants to zero
	printf("\t\t\t\tNumber of occupants initialized to (%d)!\n", (*unit_head)->number_of_occupants);
	printf("\n");
	printf("\t\t\t\t  --Unit Successfully Added!--\n");//prompt that shows successful addition of unit
	(*unit_head)->tenants = NULL;//initially make the pointer to the tenants null for further use
	(*unit_head)->next_unit = NULL;//makes the pointer to next unit NULL for further use
	(*unit_counter)++;
}
//function for adding the succeeding units
void Add_Next_Units(unit **unit_head, int *counter,int*unit_counter){
	unit *temp_unit, *traverser_unit, *validity_checker;//declared pointers that points to a unit structure
	temp_unit = (unit*)malloc(sizeof(unit));//allocating memory for the temporary unit
	validity_checker = (*unit_head);//checks if there are no duplicates
	traverser_unit = (*unit_head);//the pointer that will traverse the linked list
	printf("\t\t\tEnter name of unit: ");
	getchar();//catches the \n inputted by the user
	scanf("%[^\n]s",temp_unit->unit_name);//asks for the name of the unit
	Transform_to_Upper((temp_unit)->unit_name);//makes the string uppercase
	
	while(validity_checker!=NULL){//traverses the units
		if(strcmp(validity_checker->unit_name,temp_unit->unit_name)==0){//if a same unit_name was found 
			printf("\n");
			printf("\t\t\t\t--Duplicates are not allowed!--\n");//will print this error prompt
			(*counter)--;//counter decrements
			return;//stops the loop
		}
		validity_checker = validity_checker->next_unit;//moves to the next unit
	}
	printf("\t\t\tEnter maximum number of occupants: ");
	scanf("%d", &(temp_unit->max_occupant));//asks for the 
	temp_unit->number_of_occupants = 0; //initiliazing number of occupants to zero
	printf("\t\t\tNumber of occupants initialized to (%d)!\n", temp_unit->number_of_occupants);
	//showing the user that the occupants are initially set to 0
	printf("\n");
	temp_unit->tenants = NULL;//the pointer to the next unit was set to NULL for further use
	//loop that will determine the alphabetical order of the inputted unit names
	while(traverser_unit->next_unit != NULL && strcmp(traverser_unit->next_unit->unit_name,temp_unit->unit_name) <= 0){
		//traversing the unit until the desired position was located
		//magpopoint sa unit bago yung paglalagyan niya
			traverser_unit = traverser_unit->next_unit;//moves to the next
	}
	//if the traverser unit did not move meaning it is still pointed to head
	//and the inputted unit name is of lower order than the ones existing
	if(traverser_unit == (*unit_head) && strcmp(traverser_unit->unit_name,temp_unit->unit_name)>=0){ //will add to head
		temp_unit->next_unit = (*unit_head); //the temp_unit will point to where the unit  head pointer points
		(*unit_head) = temp_unit;//last step is for the unit head pointer to point to where temp_unit points
	}else{//else is to add in the middle or at tail
		temp_unit->next_unit = traverser_unit->next_unit;//temp unit will point to the next unit pointed by the traversing unit pointer
		traverser_unit->next_unit = temp_unit;//the next unit pointer of the traversing pointer will point to where temp points
	}
	temp_unit->unit_id = (*counter);//assigning the counter as the id of the unit
	(*unit_counter)++;
	printf("\t\t\t\t   --Unit Successfully Added!--\n");//prompt that shows succesfull add of unit
}
//function that prints all the recorded units 
void Recorded_Units(unit *unit_head){
	unit *temp_unit;
	temp_unit = unit_head;
	//this print function shows the details of a unit together with the remaining slots for occupancy
	while(temp_unit != NULL){
		printf("\t\t\t====================================================\n");
		printf("\t\t\t|Unit Name: %s                            \n", temp_unit->unit_name);
		printf("\t\t\t|Unit ID: [%d]                                      \n", temp_unit->unit_id );
		printf("\t\t\t|Maximum number of Occupants: %d                    \n",temp_unit->max_occupant );
		printf("\t\t\t|Number of Occupants: %d                            \n", temp_unit->number_of_occupants);
		printf("\t\t\t|Remaining slots for occupancy:[%d]                 \n", (temp_unit->max_occupant) - (temp_unit->number_of_occupants));
		printf("\t\t\t====================================================\n");
		printf("\n");
		temp_unit = temp_unit->next_unit;//moves to the next unit
	}
}
int is_valid_number(char str[]){
	int i;
	if(strlen(str)==0) return 0;

	for(i=0;i<strlen(str);i++){
		if(!isdigit(str[i])){
			return 0;
		} 
	}
	return 1;
}
//function to add tenants
void Add_Tenant(unit **unit_head, tenant **tenant_head){
	unit *temp_unit;//declaring temp unit pointer that points to a unit structure
	unit *validity_checker1;//checks for the duplicates
	tenant *validity_checker2;//checks for the duplicates
	int choice;//will store the id of the chosen unit
	char temp_first[100];//temporary first name that will be subjected to duplicate checking
	char temp_last[100];//temporary last name that will be subjected to duplicate checking
	validity_checker1 = (*unit_head);//checker1 also points to where unit_head pointer points
	temp_unit= (*unit_head);//same with the temp unit pointer
	if((*unit_head)==NULL){//if there are no units yet will print this prompts
		printf("\t\t\t\tThere are no units yet! Add units first!\n");
		return;
	}
		//will print the current units available 
	printf("t\t\t\t\t     Here are the current units: \n");
	printf("\n");
	Recorded_Units(*unit_head);//function call to print all the recorded units
	printf("\t\t\t     What unit do you want to occupy[unit ID]? ");
	scanf("%d", &choice);//asks for the id of the unit the user want to occupy
	printf("\n");
	while(temp_unit!=NULL){//will search for the unit
		if(temp_unit->unit_id == choice){//if the id matches then the the prompt will print that the unit is found
			printf("\t\t\t\t\t  --Unit Found!--\n");
			printf("\n");
			break;
		}
		temp_unit = temp_unit->next_unit;//moves to the next unit
	}
	if(temp_unit==NULL){
		printf("\t\t\t\t\t--Unit cannot be found!--\n");
		return;
	}
	//if the user already made a choice, the program will then check if there is still vacant slots for occupancy
	if((temp_unit->max_occupant-temp_unit->number_of_occupants)==0){
		//if the difference between the max occupant and the number occupants is 0
		//will print this prompt
		printf("\t\t\t\t--This unit is already full!--\n");
		return;
	}
	//will check if the unit exists
	if(temp_unit == NULL){
		printf("\t\t\t\t--Unit cannot be found!--\n");
		return;
	}
		//prompt showing in what unit the user
	printf("\t\t\t\t  --Adding you to Unit: [%s]--\n", temp_unit->unit_name );
	printf("\n");
	printf("\t\t\t\t  Enter First Name: ");
	getchar();
	scanf("%[^\n]s",temp_first);//gets the temporary first name
	Transform_to_Upper(temp_first);//capitalizes it
	printf("\t\t\t\t  Enter Last Name: ");
	getchar();
	scanf("%[^\n]s",temp_last);//gets the temporary last name
	Transform_to_Upper(temp_last);//capitalizes it
	validity_checker1 = (*unit_head);//checker1 points to where unit head points
	while(validity_checker1!=NULL){//traverses the units
		validity_checker2 = (validity_checker1)->tenants;//checker2 points to the first of the tenants
		while(validity_checker2!=NULL){//traverses the tenants
			if(strcmp(validity_checker2->last_name,temp_last)==0 && strcmp(validity_checker2->first_name,temp_first)==0){
				//matching first name and last name will be found
				printf("\n");
				printf("\t\t\t\t--This tenant is already registered!--\n");
				printf("\n");
				return;
			}
			validity_checker2 = validity_checker2->next_tenant;//moves to the next tenant
		}
		if(validity_checker2!=NULL){//kapag nakahanap na ng duplicate break na agad para di na magawa yung susunod
			break;
		}
		validity_checker1 = validity_checker1->next_unit;//moves to the next unit
	}

	if(temp_unit->tenants == NULL){//wala pang ibang tenant
		tenant *temp_tenant;//declaring a pointer that points to a structure tenant
		temp_tenant = (tenant*)malloc(sizeof(tenant));//allocating memory for the tenant structure
		strcpy(temp_tenant->first_name,temp_first);//copies the temporary first into the actual tenant first name
		strcpy(temp_tenant->last_name,temp_last);//copies the temporary first into the actual tenant last name
		while(1){//checks if the number is of the format [XXXXXXXXXXX]
			char temp_cp_number[128];
			printf("\t\t\t\tEnter New Contact Number: ");
			scanf("%s",temp_cp_number);
			int digit_checker = is_valid_number(temp_cp_number);//digit_checker stores the return value of the function call
			if(digit_checker!=0){
				if(strlen(temp_cp_number)==11){//checks if the entered number is of the 11-digit phone number format
					printf("\n");
					printf("\t\t\t\t\t--Valid number!--\n");
					strcpy(temp_tenant->cp_number,temp_cp_number);//copies the valid number to the actual location of cp_number
					break;//will break if successfull
				}else{
					printf("\t\t\t--This is not a valid number! Follow this format [XXXXXXXXXXX]--\n");
				}
			}else{//otherwise will print this prompt
				printf("\t\t\t--This is not a valid number! Follow this format [XXXXXXXXXXX]--\n");
			}
		}
		printf("\t\t\t\t\t  --success!--\n");
		
		strcpy(temp_tenant->unit_occupied,temp_unit->unit_name);//copies the unit name to be the unit occupied
		(*tenant_head) = temp_unit->tenants; //make this tenant the head tenant
		temp_unit->tenants = temp_tenant;//the tenant pointer of the unit will point to the first tenant
		temp_tenant->next_tenant = NULL;//the next tenant pointer will be made NULL for further use
		temp_unit->number_of_occupants++;//number of occupants increases
		printf("\n");
		printf("\t\t\t\t  --Tenant Successfully Added!--\n");//prompt showing successful addition of tenant
	}else{//succeeding tenants
		tenant *temp_tenant;//declaring a pointer that points to a structure tenant
		(*tenant_head)=temp_unit->tenants;//tenant head pointer points to the first tenant
		temp_tenant = (tenant*)malloc(sizeof(tenant));//allocating memory for the new tenant
		strcpy(temp_tenant->first_name,temp_first);//copies the temporary first into the actual tenant first name
		strcpy(temp_tenant->last_name,temp_last);//copies the temporary first into the actual tenant last name
		while(1){//checks if the number is of the format [XXXXXXXXXXX]
			char temp_cp_number[128];
			printf("\t\t\t\tEnter New Contact Number: ");
			scanf("%s",temp_cp_number);
			int digit_checker = is_valid_number(temp_cp_number);//digit_checker stores the return value of the function call
			if(digit_checker!=0){
				if(strlen(temp_cp_number)==11){//checks if the entered number is of the 11-digit phone number format
					printf("\n");
					printf("\t\t\t\t\t--Valid number!--\n");
					strcpy(temp_tenant->cp_number,temp_cp_number);//copies the valid number to the actual location of cp_number
					break;//will break if successfull
				}else{
					printf("\t\t\t--This is not a valid number! Follow this format [XXXXXXXXXXX]--\n");
				}
			}else{//otherwise will print this prompt
				printf("\t\t\t--This is not a valid number! Follow this format [XXXXXXXXXXX]--\n");
			}
		}
		printf("\t\t\t\t\t  --success!--\n");
		printf("\t\t\t\t  --Tenant Successfully Added!--\n");//prompt showing successful addition of tenant
		strcpy(temp_tenant->unit_occupied,temp_unit->unit_name);//copies the unit name to be the unit occupied
		while((*tenant_head)!=NULL){//traverses the tenants
			if(strcmp(temp_tenant->last_name,(*tenant_head)->last_name)==0){//if there is the same last name
				if(strcmp(temp_tenant->first_name,(*tenant_head)->first_name)<0){
					//magkaiba na yung first name nila, mas lower yung order (ex. carla lower than carlo)
					break;
				}
			}else{
				if(strcmp(temp_tenant->last_name,(*tenant_head)->last_name)<0){ //magkaiba ng last name tas mas mataas
					break;
				}
			}
			(*tenant_head)=(*tenant_head)->next_tenant;//moves to the next tenant
		}
		if(temp_unit->tenants == (*tenant_head)){//the tenant pointer of the unit structure still points to the tenant head
			//meaning di gumalaw, kaya sa head magdadagdag
			temp_tenant->next_tenant = (*tenant_head);//next tenant pointer will point to the tenant head
			temp_unit->tenants = temp_tenant;//the tenants pointer of the unit structure will point to the tenant added
			(*tenant_head) = temp_tenant;//the tenant head will point to the new head tenant
		}else{
			tenant *traversing_tenant;//pointer that will traverse the tenants
			traversing_tenant = temp_unit->tenants;//will point to the first tenant in the list
			while(traversing_tenant->next_tenant!=NULL){
				if(traversing_tenant->next_tenant==(*tenant_head)){
					break;
				}
				traversing_tenant=traversing_tenant->next_tenant;//moves to the next tenant
			}
			//will add in the middle/tail
			temp_tenant->next_tenant = (*tenant_head);
			traversing_tenant->next_tenant = temp_tenant;
		}
		temp_unit->number_of_occupants++;//number of occupants increments

	}
}
//function to search tenant
void Search_Tenant(unit **unit_head){
	unit *temp_unit;//declares a pointer that points to structure unit
	int success = 0;//checker if tenant exist
	char temp_first[100], temp_last[100];
	temp_unit = (*unit_head);
	if((*unit_head)==NULL){//if there is nothing yet in the list
		printf("\t\t\t\tThere is nothing to display yet!\n");
		return;
	}
	printf("\t\t\t====================================================\n");
	printf("\t\t\t       You are currently searching for a tenant.\n");
	printf("\t\t\t====================================================\n");
	printf("\t\t\t         Enter First Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_first);//gets the temporary first name
	Transform_to_Upper(temp_first);//capitalizes it
	printf("\t\t\t         Enter Last Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_last);//gets the temporary last name
	printf("\n");	
	Transform_to_Upper(temp_last);//capitalizes it

	while(temp_unit!=NULL){//traverses the units
		tenant *temp_tenant;//declaring a pointer that points to a tenant structure
		temp_tenant = temp_unit->tenants;//temp tenant points to the first tenant in the list
		while(temp_tenant!=NULL){//traverses all the tenants across units
			if(strcmp(temp_tenant->last_name,temp_last)==0 && strcmp(temp_tenant->first_name,temp_first)==0){
			//if found the matching tenant
			printf("\t\t\t====================================================\n");	
			printf("\t\t\t|       Displaying all the details of the Tenant: \n");
			printf("\t\t\t====================================================\n");
			printf("\t\t\t|\t     Unit Occupied: %s\n",temp_tenant->unit_occupied);
			printf("\t\t\t|\t     Full Name: %s, %s\n",temp_tenant->last_name,temp_tenant->first_name);
			printf("\t\t\t|\t     Contact Number: %s\n",temp_tenant->cp_number);
			printf("\t\t\t====================================================\n");
			printf("\n");
			printf("\n");
			success++;
			}
		temp_tenant = temp_tenant->next_tenant;//moves to the next tenant
			//sucess increments
		}
		temp_unit = temp_unit->next_unit;	//moves to the next unit
	}//otherwise if it did not enter the while loop, the tenant does not exist
	if(success == 0){
		printf("\t\t\t\t --This tenant does not exist!--\n");
		printf("\n");
		printf("\n");
	}
}
//function to move tenant
void Move_Tenant(unit **unit_head,tenant **tenant_head,int *counter){
	unit *temp_unit;//declaring a pointer that points to unit structure
	unit *current_unit;//will point to current unit of the tenant to be moved
	int choice_unit;//will store the id of the unit of choice
	int success=0,success2=0;
	char temp_first[100], temp_last[100];//will store the temporary first and last names
	temp_unit = (*unit_head);//temp unit points to where the head points
	//prints the asked details about the tenants	
	if((*unit_head)==NULL){
		printf("\t\t\t\tThere are no tenants to be moved!\n");
		return;
	}
	else if((*counter)==1){//meaning there are no other units to move into
		printf("\t\t\tThere are no other units to move into! Add unit first!\n");
		printf("\n");	
		return;
	}
	printf("\t\t\t====================================================\n");
	printf("\t\t\t       You are currently moving a tenant.\n");
	printf("\t\t\t====================================================\n");
	printf("\t\t\t         Enter First Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_first);//gets the temporary first name
	Transform_to_Upper(temp_first);//capitalizes it
	printf("\t\t\t         Enter Last Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_last);//gets the temporary first name
	printf("\n");	
	Transform_to_Upper(temp_last);//capitalizes it
	tenant *temp_tenant;//declaring a pointer that points to a tenant structure
	while(temp_unit!=NULL){//traverses the units 
		temp_tenant = temp_unit->tenants;
		while(temp_tenant!=NULL){
			if(strcmp(temp_tenant->last_name,temp_last)==0 && strcmp(temp_tenant->first_name,temp_first)==0){
			//nahanap yung tenant na gustong mahanap
				//will break
				break;
			}
			temp_tenant=temp_tenant->next_tenant;//if not, moves to the next tenant
		}
		if(temp_tenant!=NULL){ //para di na magnext unit kasi nahanap na
			break;
		}
		temp_unit=temp_unit->next_unit;	//if not moves to the next unit
	}
	
	current_unit = temp_unit;//current unit points to where temp unit points

	if(temp_tenant==NULL){//umabot sa dulo pero wala pa ding nakita na matching tenant
		printf("\t\t\t\t   --Tenant cannot be found!--\n");//will print this prompt
		return;
	}
	unit *temp2_unit = (*unit_head);

	while(temp2_unit!=NULL){//iterates over the list and prints the available units
		if((temp2_unit->max_occupant-temp2_unit->number_of_occupants)!=0){
			printf("\t\t\t====================================================\n");
			printf("\t\t\t|          Unit Name: %s                            \n", temp2_unit->unit_name);
			printf("\t\t\t|          Unit ID: [%d]                                   \n", temp2_unit->unit_id );
			printf("\t\t\t|          Maximum number of Occupants: %d                 \n",temp2_unit->max_occupant );
			printf("\t\t\t|          Number of Occupants: %d                         \n", temp2_unit->number_of_occupants);
			printf("\t\t\t|          Remaining slots for occupancy:[%d]              \n", (temp2_unit->max_occupant) - (temp2_unit->number_of_occupants));
			printf("\t\t\t====================================================\n");
			printf("\n");
			success++;
			}

		temp2_unit=temp2_unit->next_unit;
	}
	if(success==0){
		printf("\t\t\t\t--There are no vacant units!--\n");
		return;
	}

	printf("\t\t\t    Which unit do you want to move in?[Unit ID]: ");
	scanf("%d",&choice_unit);//asks for the id of the desired unit to move into
	unit *traverser_unit;//declaring a traversing pointer that points to a unit structure
	traverser_unit = (*unit_head);//points to where the head points
	while(traverser_unit!=NULL){//tagahanap ng unit
		if(traverser_unit->unit_id == choice_unit){//checks if the unit id matches with the choice 
			printf("\t\t\t\t\t    --Unit Found!--\n");
			printf("\n");
			success2++;
			break;
		}
		traverser_unit = traverser_unit->next_unit;//moves to the next unit
	}
	if(success2 == 0){
		printf("\t\t\t\t    --This unit cannot be found!\n");
		return;
	}
	if((traverser_unit->max_occupant-traverser_unit->number_of_occupants)==0){
		printf("\t\t\t     --You cannot move in this unit! Unit full!--\n");
		return;
	}


	tenant *copy_tenant; //declaring pointer that points to a tenant structure
	copy_tenant = (tenant*)malloc(sizeof(tenant));//allocating memory for the tenant to be moved
	strcpy(copy_tenant->first_name,temp_tenant->first_name);//copies the first name to the new copy tenant 
	strcpy(copy_tenant->last_name,temp_tenant->last_name);//copies the last name to the new copy tenant 
	strcpy(copy_tenant->cp_number,temp_tenant->cp_number);//copies the contact number to the new copy tenant 
	strcpy(copy_tenant->unit_occupied,traverser_unit->unit_name);//copies the unit name to the new copy tenant 

	(*tenant_head) = traverser_unit->tenants;//tenant head points to the first tenant in the list
		while((*tenant_head)!=NULL){//traverses the tenants
			//same function with the add tenant,compares if there are same last names
			//then checks the order of the first name to determine to place to add
			if(strcmp(copy_tenant->last_name,(*tenant_head)->last_name)==0){
				if(strcmp(copy_tenant->first_name,(*tenant_head)->first_name)<0){
					break;
				}
			}else{
				if(strcmp(copy_tenant->last_name,(*tenant_head)->last_name)<0){ //magkaiba ng last name tas mas mataas
					break;
				}
			}
			(*tenant_head)=(*tenant_head)->next_tenant;//moves to the next tenant
		}
		if(traverser_unit->tenants == (*tenant_head)){//will add at head
			copy_tenant->next_tenant = (*tenant_head);
			traverser_unit->tenants = copy_tenant;
			(*tenant_head) = copy_tenant;		
		}else{//will add at middle/tail
			tenant *traversing_tenant;//declaring a pointer that points to a tenant structure
			traversing_tenant = traverser_unit->tenants;//this traversing tenant points to the first tenant in the list
			while(traversing_tenant->next_tenant!=NULL){
				if(traversing_tenant->next_tenant==(*tenant_head)){
					break;
				}
				traversing_tenant=traversing_tenant->next_tenant;
			}
			copy_tenant->next_tenant = (*tenant_head);
			traversing_tenant->next_tenant = copy_tenant;
		}
		printf("\t\t\t\t    --Tenant Moved Succesfully!--\n");
		traverser_unit->number_of_occupants++;//number of occupants increments
		//after copying the tenant into another unit
		//will delete it in this unit
		if(temp_tenant == current_unit->tenants){//will delete at head
			current_unit->tenants = current_unit->tenants->next_tenant;
			//maintains the link, connects to the tenant after the to_be_deleted tenant
			free(temp_tenant);//frees the location of the tenant to be deleted
			current_unit->number_of_occupants--;//decrements the number of occupants in the unit
		}else{//will delete at middle/tail
			tenant *traversing_tenant2;//another pointer that points to a tenant structure
			traversing_tenant2 = current_unit->tenants;//this points to the first tenant in the current unit
			while(traversing_tenant2!=NULL){//traversing the tenants hahanaping kung nasa middle/tail
				if(traversing_tenant2->next_tenant == temp_tenant){
					//kapag nakita na tigil na
					break;
				}
				traversing_tenant2=traversing_tenant2->next_tenant;//if not, move to the next tenant
			}
			traversing_tenant2->next_tenant=temp_tenant->next_tenant;
			//maintains the link,connects to the tenant after the to_be_deleted tenant
			free(temp_tenant);//frees the location of the to_be_deleted tenat
			current_unit->number_of_occupants--;//number of occupants decrements
		}
}
//function to remove tenant
void Remove_Tenant(unit **unit_head){
	unit *temp_unit;
	tenant *to_del;//delete pointer
	char temp_first[100], temp_last[100];//stores the temporary data
	char decision1[5],decision2[5],decision3[5];//stores the decision to delete/not
	temp_unit = (*unit_head);
	if((*unit_head)==NULL){//there are currently nothing to delete
		printf("\t\t\t\tThere are no tenants to be removed!\n");
		return;
	}
	printf("\t\t\t====================================================\n");
	printf("\t\t\t       You are currently removing a tenant.\n");
	printf("\t\t\t====================================================\n");
	printf("\t\t\t         Enter First Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_first);
	Transform_to_Upper(temp_first);//capitalize it
	printf("\t\t\t         Enter Last Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_last);
	printf("\n");	
	Transform_to_Upper(temp_last);//capitalize it
	tenant *temp_tenant;
	while(temp_unit!=NULL){//traverses the units
		temp_tenant = temp_unit->tenants;//points to the first tenant in the unit
		while(temp_tenant!=NULL){//traverses the tenants till founds the matching tenant with the input
			if(strcmp(temp_tenant->last_name,temp_last)==0 && strcmp(temp_tenant->first_name,temp_first)==0){
			printf("\t\t\t\t     --Tenant matched!--\n");
			break;//will break if found already
			}
			temp_tenant=temp_tenant->next_tenant;//moves to the next tenant
		}
		if(temp_tenant!=NULL){//tigil na agad para di na gawin yung susunod
			break;
		}
		temp_unit=temp_unit->next_unit;//moves to the next unit
	}
	if(temp_unit==NULL){//if there is no matching tenant with the input
		printf("\t\t\t\t--Tenant cannot be found!--\n");
		return;
	}
	//prompts asking if the user is really sure with the decision to delete
	printf("\t\t\tAre you sure you want to delete this tenant? y/n  ");
	scanf("%s",decision1);
	if(strcmp("y",decision1)==0){
		printf("\t\t\tAre you really really sure you want to do this? y/n  ");
		scanf("%s",decision2);
		if(strcmp("y",decision2)==0){
			printf("\t\t\tThis is your last chance. There's no going back. y/n " );
			scanf("%s",decision3);
			if(strcmp("y",decision3)==0){
				printf("\n");
				printf("\t\t\t\t     --Deleting Tenant...--\n");
				printf("\n");
				printf("\t\t\t       --Tenant Deleted Successfully!--\n");//deleted successfully
				printf("\n");
				if(temp_tenant == temp_unit->tenants){//deleting at head
					temp_unit->tenants = temp_tenant->next_tenant;//points to the next tenant to preserve the link
					free(temp_tenant);//frees that temporary pointer to the to be deleted tenant
					if(temp_unit==NULL){
						temp_unit->tenants=NULL;
					}
					temp_unit->number_of_occupants--;//decrements the number of occupants in the unit
				}else{
					tenant *traversing_tenant;
					traversing_tenant = temp_unit->tenants;//points to the first tenant in the unit
					while(traversing_tenant!=NULL){//nasa middle/tail ang idedelete
						if(traversing_tenant->next_tenant == temp_tenant){//the tenant to be deleted was found
							break;//will break
						}
						traversing_tenant=traversing_tenant->next_tenant;//else, move to the next tenant
					}
					traversing_tenant->next_tenant=temp_tenant->next_tenant;//points to the next tenant to preserve the link
					free(temp_tenant);//frees the temporary pointer holding the location of the to be deleted tenant
					temp_unit->number_of_occupants--;//decrements the number of occupants in the unit
				}
			}else{
				if(strcmp("n",decision3)==0){//otherwise
					printf("\n");
					printf("\t\t\t    --It took you so long to decide. Returning...--\n");
					return;
				}else{
			printf("\t\t\t\t\t--y/n only!--\n");
				}
			}		
		}else{
			if(strcmp("n",decision2)==0){
				printf("\n");
				printf("\t\t\t --Good choice. Cancelling deletion. Returning...--\n");
				return;
			}else{
			printf("\t\t\t\t\t--y/n only!--\n");
			}
		}
	}else{
		if(strcmp("n",decision1)==0){
			printf("\n");		
			printf("\t\t\t\t --Cancelling deletion. Returning...--\n");
			return;
		}else{
			printf("\t\t\t\t\t--y/n only!--\n");
		} 
	}	
//function to edit tenant
}
void Edit_Tenant(unit **unit_head){
	unit *temp_unit;
	int success = 0,success2=0;
	char temp_first[100],temp_last[100],temp_cp_number[100];//will store the temporary data
	char choice[5];
	temp_unit = (*unit_head);
	if((*unit_head)==NULL){//if there is nothing yet in the list
		printf("\t\t\t\tThere is nothing to edit yet!\n");
		return;
	}
	printf("\t\t\t====================================================\n");
	printf("\t\t\t       You are currently editing a tenant.\n");
	printf("\t\t\t====================================================\n");
	printf("\t\t\t         Enter First Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_first);//gets the temporary first name
	Transform_to_Upper(temp_first);//capitalizes it
	printf("\t\t\t         Enter Last Name of Tenant: ");
	getchar();
	scanf("%[^\n]s",temp_last);//gets the temporary first name
	printf("\n");	
	Transform_to_Upper(temp_last);//capitalizes it
	tenant *temp_tenant;//declaring a pointer that points to a tenant structure
	while(temp_unit!=NULL){//traverses the units 
		temp_tenant = temp_unit->tenants;
		while(temp_tenant!=NULL){
			if(strcmp(temp_tenant->last_name,temp_last)==0 && strcmp(temp_tenant->first_name,temp_first)==0){
			//nahanap yung tenant na gustong mahanap
				//will break
				success2++;
				break;
			}
			temp_tenant=temp_tenant->next_tenant;//if not, moves to the next tenant
		}
		if(temp_tenant!=NULL){ //para di na magnext unit kasi nahanap na
			break;
		}
		temp_unit=temp_unit->next_unit;	//if not moves to the next unit
	}
	if(success2 != 0) printf("\t\t\t\t   --Tenant Matched!--\n");
	if(temp_tenant==NULL){//umabot sa dulo pero wala pa ding nakita na matching tenant
		printf("\t\t\t\t   --Tenant cannot be found!--\n");//will print this prompt
		return;
	}
	printf("\t\t\tOnly the contact number can be edited. Would you like to continue? y/n " );//prompt na nagsasabing cp number lang pwede iedit
	scanf("%s",choice);
	if(strcmp("y",choice)==0){//strcmp ng choice with y
		printf("\n");
		printf("\t\t\tVery well! Editing contact number of Mr/Ms. %s %s\n", temp_first,temp_last );
		
		while(1){//checks if the number is of the format [XXXXXXXXXXX]
			char temp_cp_number[128];
			printf("\t\t\t\tEnter New Contact Number: ");
			scanf("%s",temp_cp_number);
			int digit_checker = is_valid_number(temp_cp_number);//digit_checker stores the return value of the function call
			if(digit_checker!=0){
				if(strlen(temp_cp_number)==11){//checks if the entered number is of the 11-digit phone number format
					printf("\n");
					printf("\t\t\t\t\t--Valid number!--\n");
					strcpy(temp_tenant->cp_number,temp_cp_number);//copies the valid number to the actual location of cp_number
					break;//will break if successfull
				}else{
					printf("\t\t\t--This is not a valid number! Follow this format [XXXXXXXXXXX]--\n");
				}
			}else{//otherwise will print this prompt
				printf("\t\t\t--This is not a valid number! Follow this format [XXXXXXXXXXX]--\n");
			}
		}
		printf("\t\t\t\t\t  --success!--\n");
		
	}else{
		if(strcmp("n",choice)==0){//otherwise
			printf("\n");
			printf("\t\t\t\t\t\t--Okay! :)--\n");
			return;
		}else{
			printf("\t\t\t\t\t--y/n only!--\n");
		}
	}
}
//function to print masterlist 
void print_Masterlist(unit *unit_head){
	unit *temp_unit;
	if(unit_head == NULL){//the list is currently empty
		printf("\t\t\t\tThere is nothing to display yet!\n");
		return;
	}
	temp_unit = (unit_head);
	while(temp_unit!=NULL){//iterates over the list and prints the available units
		printf("\t\t\t====================================================\n");
		printf("\t\t\t|          Unit Name: %s                            \n", temp_unit->unit_name);
		printf("\t\t\t|          Unit ID: [%d]                                   \n", temp_unit->unit_id );
		printf("\t\t\t|          Maximum number of Occupants: %d                 \n",temp_unit->max_occupant );
		printf("\t\t\t|          Number of Occupants: %d                         \n", temp_unit->number_of_occupants);
		printf("\t\t\t|          Remaining slots for occupancy:[%d]              \n", (temp_unit->max_occupant) - (temp_unit->number_of_occupants));
		printf("\t\t\t====================================================\n");
		printf("\n");
		tenant *temp_tenant;
		temp_tenant = temp_unit->tenants;
		while(temp_tenant!=NULL){//iterates over the tenants and prints all the available tenants
			printf("\t\t\t\t\t=Occupants= \n");
			printf("\t\t\t\t\t\t||Full Name: %s, %s\n", temp_tenant->last_name,temp_tenant->first_name);
			printf("\t\t\t\t\t\t||Contact Number: %s\n",temp_tenant->cp_number );
			printf("\n");
			temp_tenant = temp_tenant->next_tenant;//moves to the next tenants
		}
		temp_unit = temp_unit->next_unit;//moves to the next unit
	}
}
//function to print all tenants per unit
void Occupants_Per_Unit(unit *unit_head){
	unit *temp_unit;
	int success = 0;
	char choice_unit[100];
	temp_unit = unit_head;

	if(unit_head == NULL){//there are no data in the list yet
		printf("\t\t\t\tThere is nothing to display yet!\n");
		return;
	}

	printf("\t\t\t\t     Enter Name of Unit: ");//asks for the unit
	getchar();
	scanf("%[^\n]s",choice_unit);//
	Transform_to_Upper(choice_unit);//capitalize the unit 

	while(temp_unit!=NULL){//will traverse all the available units in the list
		if(strcmp(temp_unit->unit_name,choice_unit)==0){//searches for the matching unit
			printf("\t\t\t\t\t--Unit Found!--\n");//success
			printf("\n");
			if(temp_unit->tenants==NULL){//if there are no occupants
				printf("\t\t\t====================================================\n");
				printf("\t\t\t|    There are curently no occupants in this unit \n");
				printf("\t\t\t====================================================\n");
				success++;//success increments
			}else{//otherwise,there are already occupants
				printf("\t\t\t====================================================\n");
				printf("\t\t\t|                Here are the occupants: \n");
				printf("\t\t\t====================================================\n");
				tenant *temp_tenant;
				temp_tenant = temp_unit->tenants;
				while(temp_tenant!=NULL){//traverses the tenants in the unit and prints all of them
					printf("\t\t\t|\t     Full Name: %s, %s\n",temp_tenant->last_name,temp_tenant->first_name);
					printf("\t\t\t|\t     Contact Number: %s\n",temp_tenant->cp_number );
					printf("\t\t\t====================================================\n");
					printf("\n");
					temp_tenant = temp_tenant->next_tenant;//moves to the next tenant
				}
				success++;//increments the success checker
			}
		}
		temp_unit = temp_unit->next_unit;//moves to the next unit
	}
	if(success == 0){//hindi pumasok sa loop,meaning not valid
		printf("\t\t\t\t   --This unit does not exist!--\n");
		printf("\n");
		printf("\n");
	}
}
//function to remove unit
void Remove_Unit(unit **unit_head, int*counter,int *unit_counter){
	unit *temp_unit;
	int success = 0;
	char delete_unit[100];
	char decision1[5],decision2[5],decision3[5];
	temp_unit = (*unit_head);
	if((*unit_head)==NULL){//there are no units to be removed
		printf("\t\t\t\tThere are no units to be removed!\n");
		return;
	}
	printf("\t\t\t====================================================\n");
	printf("\t\t\t       You are currently removing a unit.\n");
	printf("\t\t\t====================================================\n");
	printf("\t\t\t    Enter the unit you want to delete: ");
	getchar();
	scanf("%[^\n]s", delete_unit);//asks for the unit to be deleted
	Transform_to_Upper(delete_unit);//capitalizes the unit of choice
	while(temp_unit!=NULL && strcmp(temp_unit->unit_name,delete_unit)!=0){//traverses the unit if it is not empty and haven't found the matching unit
		temp_unit=temp_unit->next_unit;//moves to the next  unit
	}
	if(temp_unit == NULL){//umabot sa dulo, meaning walang nahanap, thus showing this prompt
		printf("\t\t\t\t--Unit cannot be found!--\n");
		return;//back to menu
	}else{
		printf("\t\t\t\t\t--Unit found!--\n");
	}
	if(temp_unit->tenants !=NULL){//nahanap yung unit, pero may nakatira pa. Bawal dapat magdelete in that case
		printf("\n");
		printf("\t\t\tUnit occupied. Move/Remove occupants first before deleting this unit!\n");
		printf("\t\t\t\t\t--Returning to menu...--\n");
		printf("\n");
		return;//back to main menu
	}else{
		printf("\n");//otherwise, nahanap na and walang nakatira
		printf("\t\t\tAre you sure you want to delete this unit? y/n  ");
	scanf("%s",decision1);
	if(strcmp("y",decision1)==0){
		printf("\t\t\tAre you really really sure you want to do this? y/n  ");
		scanf("%s",decision2);
		if(strcmp("y",decision2)==0){
			printf("\t\t\tThis is your last chance. There's no going back. y/n " );
			scanf("%s",decision3);
			if(strcmp("y",decision3)==0){
				printf("\n");
				printf("\t\t\t\t     --Deleting Unit...--\n");
				printf("\n");
				printf("\t\t\t       --Unit Deleted Successfully!--\n");//the unit was deleted successfully
				printf("\n");
				if(temp_unit == (*unit_head)){//will delete at head
					(*unit_head) = temp_unit->next_unit;//points to the next unit to preserve the link
					free(temp_unit);//frees the temporary pointer holding the location of the unit to be deleted
					(*unit_counter)--;//unit counter decrements
					if((*unit_head)==NULL){
						(*counter)=0;//set counter to 0 kapag nadelete lahat ng unit para magstart ulit sa 1 ung ID
					}
				}else{
					unit *traversing_unit;
					traversing_unit = (*unit_head);//points to the head unit
					while(traversing_unit!=NULL){//will delete at middle/tail
						if(traversing_unit->next_unit == temp_unit){//the unit to be deleted was found
							break;//will break
						}
						traversing_unit=traversing_unit->next_unit;//otherwise, move to the next
					}
					traversing_unit->next_unit=temp_unit->next_unit;//points to the next unit to preserve the link
					free(temp_unit);//frees the temporary pointer holding the location of the unit to be deleted
					(*unit_counter)--;//unit counter decrements 
					}
					if((*unit_head)==NULL){
						(*counter)=0;//if nadelete na lahat ng unit,babalik yung counter sa zero
						//para di masyadong lumaki yung latest counter
					}
				}else{
					if(strcmp("n",decision3)==0){//otherwise
					printf("\n");
					printf("\t\t\tIt took you so long to decide. Returning...\n");
					return;
					}else{
						printf("\t\t\t\t\t--y/n only!--\n");
					} 
				}		
			}else{
				if(strcmp("n",decision2)==0){
					printf("\n");
					printf("\t\t\tGood choice. Cancelling deletion. Returning...\n");
					return;
					}else{
						printf("\t\t\t\t\t--y/n only!--\n");
					} 
				}		
		}else{
			if(strcmp("n",decision1)==0){
				printf("\n");
				printf("\t\t\tCancelling deletion. Returning...\n");
				return;
			}else{
				printf("\t\t\t\t\t--y/n only!--\n");
			} 
		}		
	}
}
//function to read the data stored in tenants.txt
void load(unit**unit_head,tenant**tenant_head,int*counter,int*unit_counter){
	unit *temp_unit;
	int i;
	FILE *fp;
	if(fp = fopen("tenants.txt","r")){//opens the file tenants.txt(dapat nageexist)
		if(fp!=NULL){//checks if the file exists
			printf("\t\t\t\tFile Successfully Loaded!\n");
			fscanf(fp,"%d",&(*unit_counter));//scans the total number of units
			fscanf(fp,"%d",&(*counter));//scans the latest counter used in ID-ing the units
			for(i=0;i<(*unit_counter);i++){//iterates along the value of the total units available
				temp_unit = (unit*)malloc(sizeof(unit));//allocates memory for the temporary unit
				if((*unit_head)==NULL){//first condition wala pang laman
					fgetc(fp);//get \n at the end of the fscanf
					fgets(temp_unit->unit_name,100,fp);//reads all the necessary informations in the file
					(temp_unit->unit_name)[strlen(temp_unit->unit_name)-1] = '\0';//nilalagyan ng terminating character sa end ng string
					fscanf(fp,"%d\n",&(temp_unit->unit_id));
					fscanf(fp,"%d\n",&(temp_unit->max_occupant));
					fscanf(fp,"%d\n",&(temp_unit->number_of_occupants));
					(*unit_head)=temp_unit;//head points to the temp_unit
					temp_unit->tenants = NULL;//sets the tenants to null for later use
					if((*unit_head)->number_of_occupants>0){//if there are occupants
						tenant *temp_tenant;
						for(int j=0;j<(*unit_head)->number_of_occupants;j++){//iterates over the value of the available tenants
							temp_tenant = (tenant*)malloc(sizeof(tenant));//allocating maemory for the temporary tenant
							if((temp_unit->tenants)==NULL){//first condition, wala pang laman
								fgets(temp_tenant->last_name,100,fp);//gets all the necessary informations in the file
								(temp_tenant->last_name)[strlen(temp_tenant->last_name)-1] = '\0';//nilalagyan ng terminating character yung dulo ng string
								fgets(temp_tenant->first_name,100,fp);
								(temp_tenant->first_name)[strlen(temp_tenant->first_name)-1] = '\0';
								fgets(temp_tenant->cp_number,20,fp);
								(temp_tenant->cp_number)[strlen(temp_tenant->cp_number)-1] = '\0';
								fgets(temp_tenant->unit_occupied,100,fp);
								(temp_tenant->unit_occupied)[strlen(temp_tenant->unit_occupied)-1] = '\0';
								temp_tenant->next_tenant=NULL;//sets the next tenant pointer for later use
								temp_unit->tenants = temp_tenant;//added it to the tail of the list
							}else{
								fgets(temp_tenant->last_name,100,fp);
								(temp_tenant->last_name)[strlen(temp_tenant->last_name)-1] = '\0';
								fgets(temp_tenant->first_name,100,fp);
								(temp_tenant->first_name)[strlen(temp_tenant->first_name)-1] = '\0';
								fgets(temp_tenant->cp_number,20,fp);
								(temp_tenant->cp_number)[strlen(temp_tenant->cp_number)-1] = '\0';
								fgets(temp_tenant->unit_occupied,100,fp);
								(temp_tenant->unit_occupied)[strlen(temp_tenant->unit_occupied)-1] = '\0';
								tenant *traversing_tenant;
								traversing_tenant = temp_unit->tenants;
								while(traversing_tenant->next_tenant!=NULL){
									traversing_tenant=traversing_tenant->next_tenant;
								}
								traversing_tenant->next_tenant=temp_tenant;//added it to the tail of the list
								temp_tenant->next_tenant = NULL;//sets the next tenant pointer to null for later use

							}
						}
					}
				}else{//second condition, kapag may laman na
					fgets(temp_unit->unit_name,100,fp);//gets all the necessary informations in the file
					(temp_unit->unit_name)[strlen(temp_unit->unit_name)-1] = '\0';//nilalagyan ng terminating character yung dulo ng string
					fscanf(fp,"%d\n",&(temp_unit->unit_id));
					fscanf(fp,"%d\n",&(temp_unit->max_occupant));
					fscanf(fp,"%d\n",&(temp_unit->number_of_occupants));
					unit *traversing_unit = (*unit_head);
					while(traversing_unit->next_unit!=NULL){//traverses the units til it finds the tail
						traversing_unit = traversing_unit->next_unit;
					}
					traversing_unit->next_unit = temp_unit;//adds to tail of the units
					temp_unit->tenants = NULL;//sets the tenants to null for later use
					if(temp_unit->number_of_occupants>0){//if may laman nang occupants
						tenant *temp_tenant;
						for(int j=0;j<temp_unit->number_of_occupants;j++){//iterates over the value of the available tenants
							temp_tenant = (tenant*)malloc(sizeof(tenant));//allocating memory for the temporary tenant
							if(temp_unit->tenants==NULL){//first tenant
								fgets(temp_tenant->last_name,100,fp);//gets all the necessary information in the file
								(temp_tenant->last_name)[strlen(temp_tenant->last_name)-1] = '\0';
								fgets(temp_tenant->first_name,100,fp);
								(temp_tenant->first_name)[strlen(temp_tenant->first_name)-1] = '\0';
								fgets(temp_tenant->cp_number,20,fp);
								(temp_tenant->cp_number)[strlen(temp_tenant->cp_number)-1] = '\0';
								fgets(temp_tenant->unit_occupied,100,fp);
								(temp_tenant->unit_occupied)[strlen(temp_tenant->unit_occupied)-1] = '\0';
								temp_tenant->next_tenant=NULL;//sets the next tenant to null for further use
								temp_unit->tenants = temp_tenant;//adds to the tail of the list
							}else{
								fgets(temp_tenant->last_name,100,fp);//gets all the ncessary informations in the file
								(temp_tenant->last_name)[strlen(temp_tenant->last_name)-1] = '\0';
								fgets(temp_tenant->first_name,100,fp);
								(temp_tenant->first_name)[strlen(temp_tenant->first_name)-1] = '\0';
								fgets(temp_tenant->cp_number,20,fp);
								(temp_tenant->cp_number)[strlen(temp_tenant->cp_number)-1] = '\0';
								fgets(temp_tenant->unit_occupied,100,fp);
								(temp_tenant->unit_occupied)[strlen(temp_tenant->unit_occupied)-1] = '\0';
								tenant *traversing_tenant;
								traversing_tenant=temp_unit->tenants;
								while(traversing_tenant->next_tenant!=NULL){//traverses the list til it finds the tail
									traversing_tenant=traversing_tenant->next_tenant;
								}
								traversing_tenant->next_tenant=temp_tenant;//adds to the tail of thelist
								temp_tenant->next_tenant = NULL;//sets the next tenant to null for later use
							}
						}
					}
				}
			}
		}
		fclose(fp);		//closes the file after using it
	}else{//otherwise 
		printf("\t\t\t    Failed to load file! Creating a storage file....\n");
	}	
}
//save all the data into tenants.txt
void save(unit **unit_head,tenant **tenant_head, int *counter,int*unit_counter){
	unit *temp_unit=(*unit_head);//temporary pointer points to the head pointer
	FILE *fp;//file pointer declaration
	fp = fopen("tenants.txt","w");//opening in write mode
	fprintf(fp,"%d\n",(*unit_counter));//will print the current number of units in the file
	fprintf(fp, "%d\n",(*counter));//also prints the latest counter that is used (reference for the latest UNIT ID)
	while(temp_unit!=NULL){//traverses the units
		fprintf(fp, "%s\n",temp_unit->unit_name);//prints to file the necessary details about the unit
		fprintf(fp, "%d\n",temp_unit->unit_id);
		fprintf(fp, "%d\n",temp_unit->max_occupant);
		fprintf(fp, "%d\n",temp_unit->number_of_occupants);
		tenant *temp_tenant;//declares another temporary pointer pointing to a tenant structure
		(*tenant_head) = temp_unit->tenants;//tenant head pointer points to the first tenant in the unit
		temp_tenant = (*tenant_head);		//temp_tenant now points to the first tenant in the list
		if(temp_tenant!=NULL){//checks if may tenant ba, kung wala pass lang
			while(temp_tenant!=NULL){//if meron, traverses all tenants in the unit
				fprintf(fp, "%s\n",temp_tenant->last_name);//prints to file all the necessary informations about the tenant
				fprintf(fp, "%s\n",temp_tenant->first_name);
				fprintf(fp, "%s\n",temp_tenant->cp_number);
				fprintf(fp, "%s\n",temp_tenant->unit_occupied);
				temp_tenant=temp_tenant->next_tenant;//moves to the next tenant
			}
		}
		temp_unit= temp_unit->next_unit;//moves to the next unit
	}
	fclose(fp);//closes the file
}
void free_all_allocated(unit **unit_head){
	unit *to_del;//declaring a delete pointer
	while((*unit_head)!=NULL){//traverses the linked list
		to_del = (*unit_head);//delete pointer points to the first unit of the list
		tenant *to_del2; //second delete pointer
		while((*unit_head)->tenants != NULL){//traverses the tenants of each unit
			to_del2 = (*unit_head)->tenants;//delete pointer 2 points to the first tenants of the unit
			(*unit_head)->tenants = (*unit_head)->tenants->next_tenant;//maintains the link
			//by connecting the current link to the tenants after the tenants pointed by the delete pointer
			free(to_del2);//frees the location  of the tenants currently pointed by the delete pointer2
		}
		(*unit_head) = (*unit_head)->next_unit;//the head pointer can be moved to link with the unit after the
		//unit pointed by the delete pointer1
		free(to_del);//frees the location of the current unit pointed by the delete pointer1
	}
	printf("\t\t\tAll dynamic allocated variable has been freed :)...\n");
}

