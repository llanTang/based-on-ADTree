//
//  hitonPC.cpp
//  testextern
//
//  Created by ustc@tll on 2/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "hitonPC.hpp"
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
using namespace std;
void interleave_hiton_pc(int target)

//HITON_PC for mb without symmetry Algorithm

{
    int i,j,stop,k, aux,t2,counts,last_added;
    int *pc, *order,*cond,*sep2;
    double *dep,*dep1,*dep2,t1;
    
    sep2=new int[max_max_cond_size];
    pc=new int[n_vars];
    order=new int[n_vars];
    for(i=0;i<n_vars;i++)
    {
        if(n_states[i]>1 && n_states[target]>1)
            pc[i]=0;
        else
            pc[i]=-1;
    }
    pc[target]=-1;
    
    cond=new int[max_max_cond_size+1];
    for(i=0;i<max_max_cond_size+1;i++)
        cond[i]=-1;
    
    dep=new double[n_vars];
    dep1=new double[n_vars];
    dep2=new double[n_vars];
    counts=0;
    
    
    ////odering variable according to its p-value with target variable
    
    for(i=0;i<n_vars;i++)
    {
        dep[i]=(double)0.0;
        order[i]=i; //dep ˝◊Èµƒ≥ı ºœ¬±Í
    }
    
    for(i=0;i<n_vars;i++)
        if(pc[i]==0)
        {
            
            dep[i]=compute_dep(i,target,cond);
            // printf("ddddd\n");
            
            if(dep[i]<=(double)(-1.0))
                
                pc[i]=-1;
            else
                if(dep[i]>=(double)(1.0))
                {
                    dep2[counts]=dep[i];
                    order[counts]=i;
                    counts++;
                    //printf(" Adding %d with dependence %.2f\n",i,dep[i]);
                    
                }
        }
    
    
    
    for(j=0; j<counts; ++j)
    {
        for(i=0; i<counts-j-1; ++i)
        {
            if(dep2[i]<dep2[i+1])
            {
                //Ωªªª ˝æ›
                t1=dep2[i];
                dep2[i]=dep2[i+1];
                dep2[i+1]=t1;
                
                //Ωªªª‘≠¿¥µƒœ¬±Í
                t2= order[i];
                order[i]= order[i+1];
                order[i+1]=t2;
            }
        }
    }
    
    
    //    sort(dep3,counts,order);
    
    k=0;
    do
    {
        stop=1;
        
        
        if(dep2[k]>0)
        {
            aux=order[k];
            
            pc[aux]=1;
            stop=0;
            // printf(" Adding %d with dependence %.2f\n",aux,dep2[k]);
            last_added=aux;
        }
        
        if(stop==0)
        {
            
            
            for(i=0;i<n_vars;i++)
                dep1[i]=(double)0;
            
            for(i=0;i<n_vars;i++)
                if(pc[i]==1)
                {
                    pc[i]=0;
                    dep1[i]=max_k_min_dep(i, target, -1, pc, sep2,3);
                    //dep1[i]=min_dep(i, target, -1, pc, sep2);
                    pc[i]=1;
                    
                    if(dep1[i]<=(double)(-1.0))
                    {
                        pc[i]=-1;
                        
                        //printf(" removing %d with dependence %.2f\n",i,dep1[i]);
                        
                    }
                    if(last_added==i)
                        break;
                }
            
        }
        k++;
        
    }while(stop==0);
    
    for(i=0;i<n_vars;i++)
        if(pc[i]==-1)
            pc[i]=0;
    
    //report_pc(target,pc);
    
    
    for(i=0;i<n_vars;i++)
        if(pc[i]==1)
            printf(" %d ",i);
    
    
    delete [] pc;
    delete [] dep;
    delete [] dep1;
    delete [] dep2;
    delete [] cond;
    delete [] order;
}
