//
//  testRep.cpp
//  ADTree
//
//  Created by ustc@tll on 4/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "testRep.hpp"
#include "datavar.h"
#include <time.h>
#include <math.h>
void report(int target,  int *mb)

{
    int i, j, in_mb, tp, fp, fn;
    FILE *fp_out;
    
    fp_out=fopen("/Users/ustctll/Desktop/result_mb.txt","a+");
    
    printf("\n");
    
    tp=0;
    fp=0;
    fn=0;
    
    for(i=0;i<n_vars;i++)
        if(i!=target)
        {in_mb=0;
            
            if(net[i][target]==1 || net[target][i]==1)
                in_mb=1;
            else
                for(j=0;j<n_vars;j++)
                    if(net[target][j]==1 && net[i][j]==1)
                        in_mb=1;
            
            if(mb[i]==1 && in_mb==1)
                tp++;
            else
            {if(mb[i]==1 && in_mb==0)
                fp++;
            else
                if(mb[i]==0 && in_mb==1)
                    fn++;
            }
        }
    //fprintf(fp_out,"the target %d variable MB result:\n",target);
    //fprintf(fp_out,"tp/(tp+fp)  tp/(tp+fn)  distance   time\n",target);
    
    printf("the variable %d MB result:\n",target);
    
    if(tp==0 && fp==0)
    {
        printf("\ntp==0 && fp==0:%.2f\n",(double)(-1.0));
        fprintf(fp_out,"  %f  ",(double)(-1.0));
        prec+=(double)(-1.0);
    }
    else
    {
        printf(" tp/(tp+fp): %.2f\n",(double)tp/(double)(tp+fp));
        fprintf(fp_out,"  %.2f  ",(double)tp/(double)(tp+fp));
        prec+=(double)tp/(double)(tp+fp);
    }
    
    if(tp==0 && fn==0)
    {
        printf(" tp==0 && fn==0: %.2f\n",(double)(-1.0));
        fprintf(fp_out,"   %f  ",(double)(-1.0));
        recall+=(double)(-1.0);
    }
    else
    {
        printf(" tp/(tp+fn): %.2f\n",(double)tp/(double)(tp+fn));
        fprintf(fp_out,"  %.2f  ",(double)tp/(double)(tp+fn));
        recall+=(double)tp/(double)(tp+fn);
    }
    
    if((tp==0 && fp==0) || (tp==0 && fn==0))
    {
        printf(" (tp==0 && fp==0) || (tp==0 && fn==0):%.2f\n",(double)(-1.0));
        fprintf(fp_out,"  %f  ",(double)(-1.0));
        dis+=(double)(-1.0);
    }
    else
    {
        printf(" distance=:%.2f\n",sqrt(pow((double)1.0-(double)tp/(double)(tp+fp),(double)2.0)+pow((double)1.0-(double)tp/(double)(tp+fn),(double)2.0)));
        fprintf(fp_out,"  %.2f  ",sqrt(pow((double)1.0-(double)tp/(double)(tp+fp),(double)2.0)+pow((double)1.0-(double)tp/(double)(tp+fn),(double)2.0)));
        dis+=sqrt(pow((double)1.0-(double)tp/(double)(tp+fp),(double)2.0)+pow((double)1.0-(double)tp/(double)(tp+fn),(double)2.0));
    }
    
    
    printf(" time:%d\n",(int)(clock()-clock_init)/(int)CLOCKS_PER_SEC);
    //fprintf(fp_out,"  %d\n",(int)(clock()-clock_init)/(int)CLOCKS_PER_SEC);
    printf("\n mb:");
    for(i=0;i<n_vars;i++)
        if(mb[i]==1)
        {
            printf(" %d,",i);
            fprintf(fp_out,"%d ",i);
        }
    
    
    
    fprintf(fp_out,"\n");
    fclose(fp_out);
}
