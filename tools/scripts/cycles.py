#!/usr/bin/python

import numpy as np
#import csv
#import matplotlib
#matplotlib.use('Agg')
import matplotlib.pyplot as plt 

list_file=['adpcm','tracking','fft','filter','nw','histogram','disparity','susan']


CPU = []
DMA = []
ACC = []




for key,input1 in enumerate(list_file):
    fp = open ('./app-cycle/'+ input1+'-cycles.csv','r')
    for i, line in enumerate(fp):
        if i%3 == 0:
            CPU.append(int(line))
        elif i%3 ==1:
            DMA.append(int(line))
        elif i%3 ==2:
            ACC.append(int(line))
    fp.close()
    print "CPU"
    print CPU
    print "DMA"
    print DMA
    print "ACC"
    print ACC

    N=4
    ind = np.arange(N)
    width = 0.35
    #plt.figure(key)
    p1=plt.bar(ind, CPU, width, color = '0.5' )
    p2=plt.bar(ind, DMA, width, color = '#33ff33',bottom=CPU  )
    p3=plt.bar(ind, ACC, width, color = '#3333ff',bottom= [CPU[j]+DMA[j] for j in range(len(CPU))] )


    plt.ylabel('Cycles')
    plt.title('Cycles for different baselines for '+ input1)
    plt.xticks(ind+width/2., ('B1', 'B2', 'B3', 'B4') )
    #plt.yticks(np.arange(0,81000,1000))
    plt.legend( (p1[0], p2[0],p3[0]), ('CPU', 'DMA','ACC')  )

    #plt.show()
    plt.savefig("./graphs/"+ input1.upper() +".png")

    del CPU[:]
    del DMA[:]
    del ACC[:]

exit()
