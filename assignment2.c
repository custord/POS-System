/*-------------------------------------------------------------------
*/
/* ITS60304– Assignment #2 */
/* C Programming */
/* Student Name: <NG XI ZHUEN> */
/* Student ID: <0323271> */
/*-------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME_SIZE 30
#define CODE_SIZE 10

struct itemData {
    int quantity;          // item quantity 
	double price;          // item price
	char name[NAME_SIZE];  // item name
	char code[CODE_SIZE];  // item code
};
    
void inventory( void );   // inventory prototype
void purchase( void );    // purchase prototype
void transaction( void ); // transaction prototype
void edit( void );        // edit prototype
void deletion( void );    // delete prototype


int main( void ) 
{
    int optionNum; 
     
 	printf(" ---------------------------------- \n"
	       " Grocery Retail					    \n"
		   " ---------------------------------- \n"
 		   "    1. Purchase items				\n"
 		   "    2. Edit items					\n"
		   "    3. Delete items                 \n"
		   "    4. Show inventory               \n"
  		   "    5. Show daily transaction       \n"
		   "    6. Exit                         \n");
		   
    puts("");
	printf("Enter an option number. \n");
	printf("Enter EOF to end input. \n");
	scanf("%d", &optionNum);
	puts("");

	while( optionNum != EOF ) {
	   
	    switch( optionNum ) {		   		   
		    case 1:
				purchase();   		
		      	break;
   						
		    case 2:
                edit();
				break;
								   		
		    case 3:
				deletion();
				break;
		   		
			case 4:
				inventory();
				break;
				   		
			case 5:
                transaction();				   		
				break;
				   		
			case 6:
				exit(0);
				break;
							  
			default:
				printf(" Invalid option number. Try again. \n");
								   		        
		}    //end switch
        
		puts("");		
       	printf(" ---------------------------------- \n"
	           " Grocery Retail					    \n"
		       " ---------------------------------- \n"
 		       "    1. Purchase items				\n"
 		       "    2. Edit items					\n"
	       	   "    3. Delete items                 \n"
	       	   "    4. Show inventory               \n"
  	     	   "    5. Show daily transaction       \n"
	       	   "    6. Exit                         \n");		   
        puts("");	
		printf("Enter an option number. \n");
		printf("Enter EOF to end input. \n");
		scanf("%d", &optionNum);
	}    //end while    
return 0;						
}   //end main

//function inventory
void inventory( void )
{      
	FILE *gfPtr;    // gst.txt file pointer
	FILE *nfPtr;   // ngst.txt file pointer

    struct itemData item = { 0, 0.0, "", ""};
     
	 // opens gst.txt; exits program if file cannot be opened
	if((gfPtr = fopen("gst.txt","r")) == NULL) {
		puts("File cannot be opened.");
	}			
	 //prints GST inventory table
  	puts("========================GST==========================");
   	printf("%-12s %-17s %5s %10s\n", "Item Code", "Item Name", "Item Price", "Quantity");		
   	do{   // read item code, item name, item price, item quantity from file
		fscanf( gfPtr,"%[^;];%[^;];%lf;%d\n", item.code, item.name,&item.price,&item.quantity);
		printf("%-12s %-20s %7.2lf %10d\n", item.code, item.name, item.price, item.quantity);
	}while (!feof(gfPtr));   // while not end of file
  
	puts("");		
	fclose(gfPtr);   //close gst.txt		
       //open ngst.txt   
    if((nfPtr = fopen("ngst.txt","r")) == NULL) {
		puts("File cannot be opened");
	}   
	 //prints NON-GST inventory table	
   	puts("======================Non-GST========================");
   	printf("%-12s %-17s %5s %10s\n", "Item Code", "Item Name", "Item Price", "Quantity");   		
	do{   // read item code, item name, item price, item quantity from file
		fscanf( nfPtr,"%[^;];%[^;];%lf;%d\n", item.code, item.name,&item.price,&item.quantity);
		printf("%-12s %-20s %7.2lf %10d\n", item.code, item.name, item.price, item.quantity);
	}while (!feof(gfPtr)); 
		
	fclose(nfPtr);	 // close ngst.txt 
	  
}   // end function inventory		   		        
 
// function purchase
void purchase( void )
{   
    struct itemData item = { 0, 0.0, "", ""};              
    int findresult=0, userquantity=0;    //item availability, user input quantity
    int gQuantity=0, nQuantity=0;  // GST purchase qty, NGST purchase qty
	int gstquantity=0, ngstquantity=0, totalquantity=0;  //total GST purchase, total NGST purchase, total qty
	// subtotal, GST items price, taxed price, NGST items price, total price
    double subprice=0, gstprice=0, gstprice2=0, ngstprice=0, totalprice=0;
    double gPrice, nPrice; // GST price, NGST price
    char gName[NAME_SIZE];        // GST purchase name  
    char nName[NAME_SIZE];        // NGST purchase name  
    char gCode[CODE_SIZE];        // GST purchase code  
    char nCode[CODE_SIZE];        // NGST purchase code
    char usercode[CODE_SIZE];	  // user input code	
    char receipt[2];			  // receipt prompt (Y/N)	
		
	FILE *gfPtr;    // gst.txt file pointer
	FILE *nfPtr;   // ngst.txt file pointer
    FILE *pgPtr;   // purchaseGST.txt file pointer 
    FILE *pnPtr;   // purchaseNGST.txt file pointer 
    FILE *gtempPtr;
    FILE *ntempPtr;

	// open or create GST purchases file for appending
    if((pgPtr = fopen("purchaseGST.txt","a")) == NULL) {
        puts("File could not be opened.");
    }
    // open or create Non-GST purchases file for appending
    if((pnPtr = fopen("purchaseNGST.txt","a")) == NULL) {
        puts("File could not be opened.");
    }

    printf("Enter item code, -1 to end.\n"); // user input code
    scanf("%s", usercode);
	  // run actions while not -1
    while( strcmp(usercode,"-1")!=0){
		printf("Enter item quantity.\n");
		scanf("%d", &userquantity);

    	// open gst.txt
    	if((gfPtr = fopen("gst.txt","r")) == NULL) {
    		puts("File could not be opened.");
    	}
        // open ngst.txt
        if((nfPtr = fopen("ngst.txt","r")) == NULL) {
       		puts("File could not be opened.");
    	}
            
        if((gtempPtr = fopen("tempGST.txt","w")) == NULL) {
            puts("File could not be opened.");
        }
        if((ntempPtr = fopen("tempNGST.txt","w")) == NULL) {
            puts("File could not be opened.");
        }    	

        rewind(gtempPtr);	 
		do{  // read item code, item name, item price, item quantity from gst.txt				  
			fscanf( gfPtr,"%[^;];%[^;];%lf;%d\n", item.code,item.name,&item.price,&item.quantity);
			if (strcmp( usercode, item.code)==0) {    //compare user input code and file item code
                if(userquantity>item.quantity) {
                    printf("Amount of the item available is %d.\n", item.quantity);
                    fprintf ( gtempPtr,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);	
                }
                else{
                    fprintf ( gtempPtr,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity-userquantity);
                    subprice = item.price * userquantity;   //subtotal
    			    printf("%s is RM%.2lf\n", item.name, item.price);
    			    printf("Subtotal is RM%.2lf\n", subprice);
    				// print purchases data into purchaseGST.txt
                    fprintf( pgPtr,"%s;%s;%.2lf;%.2lf;%d\n", item.code, item.name, item.price, subprice, userquantity);    
    			    findresult++;
                }
            }
			else{
                fprintf ( gtempPtr,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);		  
			}
            
		} while(!feof(gfPtr));
        fclose(gtempPtr);

        rewind(ntempPtr);
	   	// open ngst.txt	 				   					
	    do{  // read data from ngst.txt					  
	   		fscanf( nfPtr,"%[^;];%[^;];%lf;%d\n", item.code,item.name,&item.price,&item.quantity);
			if (strcmp( usercode, item.code)==0) {    //compare user input code and file item code
                if(userquantity>item.quantity) {
                    printf("Amount of the item available is %d.\n", item.quantity);
                    fprintf ( ntempPtr,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity); 
                }
                else{
                    fprintf ( ntempPtr,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity-userquantity);
                    subprice = item.price * userquantity;   //subtotal
    			    printf("%s is RM%.2lf\n", item.name, item.price);
    			    printf("Subtotal is RM%.2lf\n", subprice);
    				// print purchases data into purchaseGST.txt
                    fprintf( pnPtr,"%s;%s;%.2lf;%.2lf;%d\n", item.code, item.name, item.price, subprice, userquantity);    
    			    findresult++;
                }
            }
			else{
                fprintf ( ntempPtr,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);		  
			}
			  
	    } while(!feof(nfPtr));
        fclose(ntempPtr);

        rewind(gfPtr);
        rewind(nfPtr);
        rewind(pgPtr);
        rewind(pnPtr);
        fclose(gfPtr);     // close gst.txt
        fclose(nfPtr);    // close ngst.txt

	    if (findresult==0) 
			printf("Invalid item.\n"); 

        remove("gst.txt");
        remove("ngst.txt");
        rename("tempGST.txt", "gst.txt");
        rename("tempNGST.txt", "ngst.txt");

        puts("");
	    printf("Enter item code, -1 to end.\n");   //user input code
        scanf("%s", usercode);   

    }   //end while
    fclose(gfPtr);     // close gst.txt
	fclose(nfPtr);    // close ngst.txt
	
    printf("Print receipt? (Y/N)\n");   //prompt receipt
    scanf("%s", receipt);
	
	// print receipt if answer is Y
    if(strcmp(receipt,"Y")==0){
	    if((pgPtr = fopen("purchaseGST.txt","r")) == NULL) {
		    puts("File cannot be opened.");
	    }

	    if((pnPtr = fopen("purchaseNGST.txt","r")) == NULL) {
		    puts("File cannot be opened.");
	    }
      	// print receipt
        puts("          Receipt            ");
        puts("-----------------------------");
        printf("%s %-15s %7s\n", "Qty", "Item", "Total");  
        puts("-----------------------------");		                   

        do{ 
            fscanf( pgPtr,"%[^;];%[^;];%lf;%lf;%d\n", gCode, gName, &gPrice, &subprice, &gQuantity);
            if (gQuantity ==0)break;  
            printf("%dx  %-15s %7.2lfSR\n    %s \n", gQuantity, gCode, subprice, gName);
            gstprice += subprice;
            gstquantity += gQuantity;  

        }while (!feof(pgPtr));   
        fclose(pgPtr);   // close purchaseGST.txt

        do{    
            fscanf( pnPtr,"%[^;];%[^;];%lf;%lf;%d\n", nCode, nName, &nPrice, &subprice, &nQuantity);   
            if (nQuantity ==0)break;  
            printf("%dx  %-15s %7.2lfZR\n    %s \n", nQuantity, nCode, subprice, nName);
            ngstprice += subprice; 
            ngstquantity += nQuantity;  

            }while (!feof(pnPtr));         
        fclose(pnPtr);   // close purchaseNGST.txt

        gstprice2 = gstprice*1.06;                     //gst items price with 6% taxed               
        totalprice = gstprice2 + ngstprice;            //total price incl gst
        totalquantity = gstquantity + ngstquantity;    //total purchase quantity

        puts("-----------------------------");
        printf("TOTAL SALE INCL GST   %.2lf\n", totalprice);
        puts("-----------------------------");
        printf("Item Count %d\n", totalquantity);
        printf("%-15s%-11s%s\n", "GST SUMMARY", "AMOUNT", "TAX");
        printf("SR %s%15.2lf%8.2lf\n", "@6%", gstprice, gstprice*0.06);
        printf("ZR %s%15.2lf    0.00\n", "@0%", ngstprice);	
        printf("TOTAL %15.2lf%8.2lf\n", gstprice + ngstprice , gstprice*0.06);		
    } 	//end if

} //end function purchase

// function transaction 
void transaction( void )
{
    struct itemData item = { 0, 0.0, "", ""};      
	// user input qty, gst item qty, ngst item qty, total qty 
    int userquantity, gstquantity=0, ngstquantity=0, totalquantity=0;
	// subtotal, gst items price, +6% gst items price, ngst items price, total price 
    double subprice, gstprice=0, gstprice2=0, ngstprice=0, totalprice=0;
    char usercode[CODE_SIZE];  //user input code
      
    FILE *pgPtr;   // purchaseGST.txt(gst purchases) file pointer
    FILE *pnPtr;   // purchaseNGST.txt(ngst purchases) file pointer

	// open gst purchases file
	if((pgPtr = fopen("purchaseGST.txt","r")) == NULL) {
		puts("File cannot be opened.");
	}
	// open non-gst purchases file
	if((pnPtr = fopen("purchaseNGST.txt","r")) == NULL) {
		puts("File cannot be opened.");
	}

    //print purchase.txt content
  	puts("--------------------GST item purchase-------------------");
   	printf("%-12s %-17s %5s %10s\n", "Item Code", "Item Name", "Item Price", "Quantity");	
 			
    do{    //read item code, item name, item price, subtotal, user input quantity from gst purchases file 
        fscanf( pgPtr,"%[^;];%[^;];%lf;%lf;%d\n", item.code, item.name, &item.price, &subprice, &userquantity);
		printf("%-12s %-20s %7.2lf %10d\n", item.code, item.name, item.price, userquantity);
        gstprice+=subprice;
        gstquantity+=userquantity;        
    }while (!feof(pgPtr)); 
    fclose(pgPtr);
    puts("");
   	puts("------------------Non-GST item purchase-----------------");
   	printf("%-12s %-17s %5s %10s\n", "Item Code", "Item Name", "Item Price", "Quantity");   
    do{    //read data from non-gst purchases file 
        fscanf( pnPtr,"%[^;];%[^;];%lf;%lf;%d\n", item.code, item.name, &item.price, &subprice, &userquantity);
		printf("%-12s %-20s %7.2lf %10d\n", item.code, item.name, item.price, userquantity);
        ngstprice+=subprice; 
        ngstquantity+=userquantity;        
    }while (!feof(pnPtr)); 
    fclose(pnPtr);

    gstprice2 = gstprice*1.06;					  //gst items price with 6% taxed 
    totalprice = gstprice2 + ngstprice;			  //total price include gst
    totalquantity = gstquantity + ngstquantity;   //total purchase quantity
	// print transaction data
    puts("");
    printf("Total transaction         : %d\n", totalquantity);
    printf("Total sales               : RM %.2lf\n", totalprice);
    printf("Sales with GST            : RM %.2lf\n", gstprice2);
    printf("Sales without GST         : RM %.2lf\n", ngstprice);
    printf("GST collected             : RM %.2lf\n", gstprice*0.06);
	
}  	// end transaction function	
 
// function edit
void edit( void )
{
    struct itemData item = { 0, 0.0, "", ""};
    int newquantity, choice, findresult=0; //new quantity, edit choice, check item avaibility
    double newprice;              //new price 
    char newname[NAME_SIZE];      //new name
    char usercode[CODE_SIZE];	  // user input code	

	FILE *gfPtr;    // gst.txt file pointer
	FILE *nfPtr;    // ngst.txt file pointer
    FILE *fp1;      // temp file pointer for gst.txt
    FILE *fp2;      // temp file pointer for ngst.txt

    printf("Enter item code, -1 to end.\n"); // user input code
    scanf("%s", usercode);
	  // run actions while not -1
    while( strcmp(usercode,"-1")!=0){ 

    	// open gst.txt
    	if((gfPtr = fopen("gst.txt","r")) == NULL) {
    		puts("File could not be opened.");
    	}
        // open ngst.txt
        if((nfPtr = fopen("ngst.txt","r")) == NULL) {
       		puts("File could not be opened.");
    	}
        // open temp file    
        if((fp1 = fopen("tmpGST.txt","w")) == NULL) {
            puts("File could not be opened.");
        }
        //open temp file
        if((fp2 = fopen("tmpNGST.txt","w")) == NULL) {
            puts("File could not be opened.");
        }    	
    	 
    	do{  // read item code, item name, item price, item quantity from gst.txt				  
    		fscanf( gfPtr,"%[^;];%[^;];%lf;%d\n", item.code,item.name,&item.price,&item.quantity);
    		if (strcmp( usercode, item.code)==0) {    //compare user input code and file item code
                printf("1. Edit name    \n"     // print edit choices
                       "2. Edit price   \n"
                       "3. Edit quantity\n");
                printf("Enter an option(1/2/3).\n");
                scanf("%d", &choice);
                findresult++;   //item found
    
                if (choice==1){  // renaming function
                    printf("Enter the new name.\n");
                    scanf("%s", newname);
                    fprintf(fp1,"%s;%s;%.2lf;%d\n", item.code, newname, item.price, item.quantity);
                    printf("New name for item %s is %s.\n", item.code, newname);
                }
    
                else if(choice==2){  // repricing function
                    printf("Enter the new price.\n");
                    scanf("%lf", &newprice);
                    fprintf(fp1,"%s;%s;%.2lf;%d\n", item.code, item.name, newprice, item.quantity);
                    printf("New price for item %s is %.2lf.\n", item.code, newprice);
                }
                else if(choice==3){  //adjust quantity function
                    printf("Enter the new quantity.\n");
                    scanf("%d", &newquantity);
                    fprintf(fp1,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, newquantity);
                    printf("New quantity for item %s is %d.\n", item.code, newquantity);     
                }      
            }
    		else{  // print unedited items to temp file
                fprintf ( fp1,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);		  
    		}        
    	} while(!feof(gfPtr));
        fclose(fp1);

    	do{  // read item code, item name, item price, item quantity from ngst.txt				  
    		fscanf( nfPtr,"%[^;];%[^;];%lf;%d\n", item.code,item.name,&item.price,&item.quantity);
    		if (strcmp( usercode, item.code)==0) {    //compare user input code and file item code
                printf("1. Edit name    \n"   // print edit choices
                       "2. Edit price   \n"
                       "3. Edit quantity\n");
                printf("Enter an option(1/2/3).\n");
                scanf("%d", &choice);
                findresult++;  // item found
    
                if (choice==1){   // renaming function
                    printf("Enter the new name.\n");
                    scanf("%s", newname);
                    fprintf(fp2,"%s;%s;%.2lf;%d\n", item.code, newname, item.price, item.quantity);
                    printf("New name for item %s is %s\n", item.code, newname);
                }
    
                else if(choice==2){  // repricing function
                    printf("Enter the new price.\n");
                    scanf("%lf", &newprice);
                    fprintf(fp2,"%s;%s;%.2lf;%d\n", item.code, item.name, newprice, item.quantity);
                    printf("New price for item %s is %.2lf\n", item.code, newprice);
                }
                else if(choice==3){  // adjust quantity function
                    printf("Enter the new quantity.\n");
                    scanf("%d", &newquantity);
                    fprintf(fp2,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, newquantity);
                    printf("New quantity for item %s is %d\n", item.code, newquantity);     
                }      
            }
    		else{   // print unedited items to temp file
                fprintf ( fp2,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);		  
    		}        
    	} while(!feof(nfPtr));
    fclose(fp2);  
    rewind(gfPtr);  // rewind gst.txt file pointer
    rewind(nfPtr);  // rewind ngst.txt file pointer
    fclose(gfPtr);  // close gst.txt file pointer
    fclose(nfPtr);  // close ngst file pointer
	if (findresult==0) 
	   printf("Item not found.\n"); 

    remove("gst.txt");
    remove("ngst.txt");
    rename("tmpGST.txt", "gst.txt");   // rename temp file to gst.txt
    rename("tmpNGST.txt", "ngst.txt"); // rename temp file to ngst.txt
    puts("");
    printf("Enter item code, -1 to end.\n");   //user input code
    scanf("%s", usercode);   
    }
}  //end function edit

//function delete
void deletion( void )
{
    struct itemData item = { 0, 0.0, "", ""};
    int findresult=0;     // check item avaibility
    char usercode[CODE_SIZE];	  // user input code
    char confirm[2];	//confirmation answer

	FILE *gfPtr;    // gst.txt file pointer
	FILE *nfPtr;    // ngst.txt file pointer
    FILE *fp3;      // temp file pointer for gst.txt
    FILE *fp4;      // temp file pointer for ngst.txt

    printf("Enter item code, -1 to end.\n"); // user input code
    scanf("%s", usercode);
	  // run actions while not -1
    while( strcmp(usercode,"-1")!=0){ 

    	// open gst.txt
    	if((gfPtr = fopen("gst.txt","r")) == NULL) {
    		puts("File could not be opened.");
    	}
        // open ngst.txt
        if((nfPtr = fopen("ngst.txt","r")) == NULL) {
       		puts("File could not be opened.");
    	}
         //open temp file
        if((fp3 = fopen("tmp2GST.txt","w")) == NULL) {
            puts("File could not be opened.");
        }
          // open temp file
        if((fp4 = fopen("tmp2NGST.txt","w")) == NULL) {
            puts("File could not be opened.");
        }    	
    	 
    	do{  // read item code, item name, item price, item quantity from gst.txt				  
    		fscanf( gfPtr,"%[^;];%[^;];%lf;%d\n", item.code,item.name,&item.price,&item.quantity);
    		if (strcmp( usercode, item.code)==0) {    //compare user input code and file item code
    			findresult++;
                printf("Confirm deletion of item %s ? (Y/N)\n",item.code);   //confirm deletion
                scanf("%s", confirm);	
                // Continue deletion if answer is Y
                if(strcmp(confirm,"Y")==0){
                    if(item.quantity==0) 
                        printf("Item %s is deleted\n",item.code);   
                
                    else{
                        printf("Item quantity is not zero.\n");
                        fprintf ( fp3,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);
                    }
                }
            }
			else{
                fprintf( fp3,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);		  
    		}        
    	} while(!feof(gfPtr));
        fclose(fp3);

    	do{  // read item code, item name, item price, item quantity from ngst.txt				  
    		fscanf( nfPtr,"%[^;];%[^;];%lf;%d\n", item.code,item.name,&item.price,&item.quantity);
    		if (strcmp( usercode, item.code)==0) {    //compare user input code and file item code
    			findresult++;
                printf("Confirm deletion of item %s ? (Y/N)\n",item.code);   //confirm deletion
                scanf("%s", confirm);	
                // Continue deletion if answer is Y
                if(strcmp(confirm,"Y")==0){
                    if(item.quantity==0) 
                        printf("Item %s is deleted\n",item.code);                
                    else{
                        printf("Item quantity is not zero.\n");
                        fprintf ( fp4,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity);
                    }
                }
            }
			else{
                fprintf( fp4,"%s;%s;%.2lf;%d\n", item.code, item.name, item.price, item.quantity); //print undeleted items to temp file		  
    		}        
    	} while(!feof(nfPtr));
        fclose(fp4);

    rewind(gfPtr);
    rewind(nfPtr);
    fclose(gfPtr);  // close gst.txt file pointer
    fclose(nfPtr);  // close ngst.txt file pointer
	if (findresult==0) 
	   printf("Item not found.\n"); 

    remove("gst.txt");  
    remove("ngst.txt");
    rename("tmp2GST.txt", "gst.txt");  //rename temp file to gst.txt
    rename("tmp2NGST.txt", "ngst.txt"); //rename temp file to ngst.txt
    puts("");
    printf("Enter item code, -1 to end.\n");   //user input code
    scanf("%s", usercode);   
    }
}  //end function delete
