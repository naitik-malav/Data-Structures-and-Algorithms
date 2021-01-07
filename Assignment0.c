#include<stdio.h>

int compare(char *x, char *y){
	if( (*x) < (*y) )
    return 1;
   
    else if( (*x) > (*y) )
    return 0;
   
    else{
		x++;
		y++;
		
		if( *x != '\0' && *y!='\0')
			return compare(x,y);
    }
    return 0;
}

int main(){
	char numberPlate[2][7];
	_Bool act=0;
	while (scanf("%s",numberPlate[act]) != EOF){
		act=1-act;
		if(act==0){
			char *aptr = numberPlate[0];
			char *bptr = numberPlate[1];
			
			printf("%d\n",compare(aptr,bptr));
		}
	}
	return(0);
}
