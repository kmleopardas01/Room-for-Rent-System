#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Leopardas_T2L_project2.h"


int main(){
	int choice, counter = 0, has_tenants = 0;
	unit *unit_head = NULL;
	tenant *tenant_head = NULL;
	int unit_counter=0;

    char *filename = "image.txt"; //opening the file image.txt that contains the header
    FILE *fptr = NULL;//declaring the file pointer and initializing it to null
    FILE *fp;
 
    if((fptr = fopen(filename,"r")) == NULL){//prompt that will print if there is error in reading
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 		
    print_image(fptr);//function call to print the image header in the image.txt
 
    fclose(fptr);//closing the file

    	//do while loop for the execution of each feature
    load(&unit_head,&tenant_head,&counter,&unit_counter);
    do{
		choice = printMenu();//variable accepting the returned choice from the menu function
		switch(choice){
			case 1:
				if(unit_head == NULL){
					counter++;
					unit_head = (unit*)malloc(sizeof(unit));//allocating memory for the unit_head pointer to a unit structure
					Add_Unit(&unit_head, &counter,&unit_counter);//function call to add unit (first unit)

				}else{
					counter++;//early incrementation of the counter and will be passed as the id of the units
					Add_Next_Units(&unit_head, &counter,&unit_counter);//function call to add unit(succeeding units)
					
				}
				break;
			case 2:
				Add_Tenant(&unit_head,&tenant_head);//function call to add tenants
				break;
			case 3:
				Search_Tenant(&unit_head);//function call to search for a particular tenant
				break;
			case 4:
				Move_Tenant(&unit_head,&tenant_head,&counter);//function call to move tenant from one unit to another
				break;
			case 5:
				Remove_Tenant(&unit_head);//function call to remove a particular tenant from a unit
				break;
			case 6:
				Edit_Tenant(&unit_head);
				break;
			case 7:
				//function call to print the masterlist of the housing system
				print_Masterlist(unit_head);
				break;
			case 8:
				//function call to print each occupant of a particular unit
				Occupants_Per_Unit(unit_head);
				break;
			case 9:
				Remove_Unit(&unit_head,&counter,&unit_counter);
				
				break;
			case 10:
				//exit
				printf("\t\t\t\t--Thank you for partnering with us!--\n");
				save(&unit_head,&tenant_head,&counter,&unit_counter);
				free_all_allocated(&unit_head);
				break;	
			default:
				printf("\n\t\t\t Invalid Choice!\n");
				break;
		}//end of switch
	}while(choice!=10);
    return 0;
}