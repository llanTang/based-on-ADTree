//
//  readNet.cpp
//  adTreem
//
//  Created by ustc@tll on 4/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "readNet.hpp"
#include "datavar.h"
#include "globaldef.h"
#include <stdlib.h>
#include <iostream>
void read_net(char *net_file){
    
    FILE *fp_mb;
    char buffer[(int)MAX_LINE_LENGTH];
    char *token;
    const char *separators=" ,\t\n\r";
    
    fp_mb=fopen(net_file,"r");
    if (!fp_mb)
    {
        perror("Failed to open file");
        exit(1);
    }
    net=new int*[n_vars];
    for(int i=0;i<n_vars;i++){
        net[i] = new int[n_vars];
        fgets(buffer,(int)MAX_LINE_LENGTH,fp_mb);
        printf("%s",buffer);
        printf("\n");
        if((int)strlen(buffer)==(int)MAX_LINE_LENGTH-1)
        {printf("\n\n Exceeding MAX_LINE_LENGTH. \n\n");
            exit(0);
        }
        
        token=strtok(buffer,separators);
        for(int j=0;j<n_vars;j++)
        {
            
            
            net[i][j]=atoi(token);
            token=strtok(0,separators);
            printf("%d,",net[i][j]);
            
        }
        printf("\n");
    }
    fclose(fp_mb);
    
    
}

