# -*- coding: utf-8 -*-
"""
Created on Fri Mar 10 12:03:39 2023

@author: Joseph Chuang-Chieh Lin
reference for creating a gif: 
    https://towardsdatascience.com/how-to-create-a-gif-from-matplotlib-plots-in-python-6bec6c0c952c
"""

import pandas as pd
#import random
import numpy as np
#import scipy.stats
import matplotlib.pyplot as plt
import torch
import time
import matplotlib.animation as animation
import matplotlib.cm as cm
import imageio

font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 28}

plt.rcParams.update({'font.size': 28})


learn_rate = torch.tensor(0.1)
steps = 100
time = list(np.arange(steps))
label = 'gradient'
isRegularized = True
if (isRegularized == True):
    label += '_regularized'

example = torch.tensor([[ 0.3757, -0.8405],
                        [ 0.7536, -0.5736],
                        [ 0.8314, -0.5334],
                        [-0.4106, -0.1695],
                        [-0.4207, -0.4805],
                        [-0.4853, -0.0533],
                        [-0.6936, -0.4227],
                        [-0.4561, -0.1088],
                        [-0.6769, -0.2457],
                        [-0.6488, -0.4109]])


z0 = example[0].requires_grad_(True)
z1 = example[1].requires_grad_(True)
z2 = example[2].requires_grad_(True)
z3 = example[3].requires_grad_(True)
z4 = example[4].requires_grad_(True)
z5 = example[5].requires_grad_(True)
z6 = example[6].requires_grad_(True)
z7 = example[7].requires_grad_(True)
z8 = example[8].requires_grad_(True)
z9 = example[9].requires_grad_(True)


s0 = torch.clone(z0.detach())
s1 = torch.clone(z1.detach())
s2 = torch.clone(z2.detach())
s3 = torch.clone(z3.detach())
s4 = torch.clone(z4.detach())
s5 = torch.clone(z5.detach())
s6 = torch.clone(z6.detach())
s7 = torch.clone(z7.detach())
s8 = torch.clone(z8.detach())
s9 = torch.clone(z9.detach())


voters = [z0, z1, z2, z3, z4, z5, z6, z7, z8, z9]
s_voters = [s0, s1, s2, s3, s4, s5, s6, s7, s8, s9]

g0 = z0+z1+z2#/3
g1 = z3+z4+z5#/3
g2 = z6+z7#/2
g3 = z8+z9#/2



def reward_z8(z8X, z8Y, z9, s8, s9, g0, g1, g2, s_voters, isRegularized):
    result = []
    for i in range(z8X.shape[0]):
        tmp = []
        for j in range(z8X.shape[1]):
            z8 = torch.tensor((torch.tensor(z8X[i][j]), torch.tensor(z8Y[i][j])))
            g3 = (z8+z9).to(torch.float32)
    
            gu0 = torch.tensor([0.0])
            gu1 = torch.tensor([0.0])
            gu2 = torch.tensor([0.0])
            gu3 = torch.tensor([0.0])
            
            for v in s_voters:
                gu0 += torch.inner(g0, v)
                gu1 += torch.inner(g1, v)
                gu2 += torch.inner(g2, v)
                gu3 += torch.inner(g3, v)
                
            exp_u_all = torch.exp(torch.tensor([gu0,gu1,gu2,gu3])).sum()    
        
            pg0 = torch.exp(gu0)/exp_u_all
            pg1 = torch.exp(gu1)/exp_u_all
            pg2 = torch.exp(gu2)/exp_u_all
            pg3 = torch.exp(gu3)/exp_u_all
            r8 = pg0*torch.inner(g0/3,s8) + pg1*torch.inner(g1/3,s8) + pg2*torch.inner(g2/2,s8)+pg3*torch.inner(g3/2,s8)
            if (isRegularized == True):
                r8 = r8-torch.pow((z8-s8).norm(), 2)
            
            #r9 = pg0*torch.inner(g0/3,s9)+pg1*torch.inner(g1/3,s9)+pg2*torch.inner(g2/2,s9)+pg3*torch.inner(g3/2,s9)
            tmp.append(r8)
        result.append(tmp)
    return torch.tensor(result)


trace_X = [z8.detach().numpy()[0]]
trace_Y = [z8.detach().numpy()[1]]
x = np.linspace(-1.0, 1.0, 100)
y = np.linspace(-1.0, 1.0, 100)
X, Y = np.meshgrid(x, y)

g0 = z0+z1+z2#/3
g1 = z3+z4+z5#/3
g2 = z6+z7#/2
g3 = z8+z9#/2
Z = reward_z8(X, Y, z9.detach(), s8, s9, g0.detach(), g1.detach(), g2.detach(), s_voters, isRegularized)
fig = plt.figure(figsize = (24,16))
plt.rc('axes', labelsize=32)    # fontsize of the x and y labels

plt.imshow(Z, extent = [-1,1,-1,1], cmap = 'jet', alpha = 1)    
plt.plot(trace_X, trace_Y)
plt.plot(trace_X[-1], trace_Y[-1], '*', markersize=20, label = "reward of v8")
plt.xlabel('x-dimension')
plt.ylabel('y-dimension')
plt.colorbar()
plt.legend(loc = "upper right")
plt.savefig('tmp_'+str(0)+'_'+label+'.png')
plt.close()


for t in range(steps):
    g0 = z0+z1+z2#/3
    g1 = z3+z4+z5#/3
    g2 = z6+z7#/2
    g3 = z8+z9#/2
    
    gu0 = torch.tensor([0.0])
    gu1 = torch.tensor([0.0])
    gu2 = torch.tensor([0.0])
    gu3 = torch.tensor([0.0])
    
    for v in s_voters:
        gu0 += torch.inner(g0, v)
        gu1 += torch.inner(g1, v)
        gu2 += torch.inner(g2, v)
        gu3 += torch.inner(g3, v)
        
    exp_u_all = torch.exp(torch.tensor([gu0,gu1,gu2,gu3])).sum()    

    pg0 = torch.exp(gu0)/exp_u_all
    pg1 = torch.exp(gu1)/exp_u_all
    pg2 = torch.exp(gu2)/exp_u_all
    pg3 = torch.exp(gu3)/exp_u_all
    

    r0 = pg0*torch.inner(g0/3,s0)+pg1*torch.inner(g1/3,s0)+pg2*torch.inner(g2/2,s0)+pg3*torch.inner(g3/2,s0)
    r1 = pg0*torch.inner(g0/3,s1)+pg1*torch.inner(g1/3,s1)+pg2*torch.inner(g2/2,s1)+pg3*torch.inner(g3/2,s1)
    r2 = pg0*torch.inner(g0/3,s2)+pg1*torch.inner(g1/3,s2)+pg2*torch.inner(g2/2,s2)+pg3*torch.inner(g3/2,s2)
    r3 = pg0*torch.inner(g0/3,s3)+pg1*torch.inner(g1/3,s3)+pg2*torch.inner(g2/2,s3)+pg3*torch.inner(g3/2,s3)
    r4 = pg0*torch.inner(g0/3,s4)+pg1*torch.inner(g1/3,s4)+pg2*torch.inner(g2/2,s4)+pg3*torch.inner(g3/2,s4)
    r5 = pg0*torch.inner(g0/3,s5)+pg1*torch.inner(g1/3,s5)+pg2*torch.inner(g2/2,s5)+pg3*torch.inner(g3/2,s5)
    r6 = pg0*torch.inner(g0/3,s6)+pg1*torch.inner(g1/3,s6)+pg2*torch.inner(g2/2,s6)+pg3*torch.inner(g3/2,s6)
    r7 = pg0*torch.inner(g0/3,s7)+pg1*torch.inner(g1/3,s7)+pg2*torch.inner(g2/2,s7)+pg3*torch.inner(g3/2,s7)
    r8 = pg0*torch.inner(g0/3,s8)+pg1*torch.inner(g1/3,s8)+pg2*torch.inner(g2/2,s8)+pg3*torch.inner(g3/2,s8)
    r9 = pg0*torch.inner(g0/3,s9)+pg1*torch.inner(g1/3,s9)+pg2*torch.inner(g2/2,s9)+pg3*torch.inner(g3/2,s9)

    #'''
    if (isRegularized == True):
        r0 = r0-torch.pow((z0-s0).norm(), 2)
        r1 = r1-torch.pow((z1-s1).norm(), 2)
        r2 = r2-torch.pow((z2-s2).norm(), 2)
        r3 = r3-torch.pow((z3-s3).norm(), 2)
        r4 = r4-torch.pow((z4-s4).norm(), 2)
        r5 = r5-torch.pow((z5-s5).norm(), 2)
        r6 = r6-torch.pow((z6-s6).norm(), 2)
        r7 = r7-torch.pow((z7-s7).norm(), 2)
        r8 = r8-torch.pow((z8-s8).norm(), 2)
        r9 = r9-torch.pow((z9-s9).norm(), 2)
    #'''
    
    r0.backward(retain_graph=True)
    gradient0 = torch.clone(z0.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r1.backward(retain_graph=True)
    gradient1 = torch.clone(z1.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r2.backward(retain_graph=True)
    gradient2 = torch.clone(z2.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r3.backward(retain_graph=True)
    gradient3 = torch.clone(z3.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r4.backward(retain_graph=True)
    gradient4 = torch.clone(z4.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r5.backward(retain_graph=True)
    gradient5 = torch.clone(z5.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r6.backward(retain_graph=True)
    gradient6 = torch.clone(z6.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r7.backward(retain_graph=True)
    gradient7 = torch.clone(z7.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r8.backward(retain_graph=True)
    gradient8 = torch.clone(z8.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    r9.backward(retain_graph=True)
    gradient9 = torch.clone(z9.grad)
    #print(z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad)
    z0.grad, z1.grad, z2.grad, z3.grad, z4.grad, z5.grad, z6.grad, z7.grad, z8.grad, z9.grad = None, None, None, None, None, None, None, None, None, None
    
    z0 = torch.add(z0, gradient0*learn_rate)
    if z0.norm()>1:
        z0 = torch.div(z0, z0.norm())
    z0 = z0.detach().requires_grad_(True)
    z1 = torch.add(z1, gradient1*learn_rate)
    if z1.norm()>1:
        z1 = torch.div(z1, z1.norm())    
    z1 = z1.detach().requires_grad_(True)
    z2 = torch.add(z2, gradient2*learn_rate)
    if z2.norm()>1:
        z2 = torch.div(z2, z2.norm())    
    z2 = z2.detach().requires_grad_(True)
    z3 = torch.add(z3, gradient3*learn_rate)
    if z3.norm()>1:
        z3 = torch.div(z3, z3.norm())    
    z3 = z3.detach().requires_grad_(True)
    z4 = torch.add(z4, gradient4*learn_rate)
    if z4.norm()>1:
        z4 = torch.div(z4, z4.norm())    
    z4 = z4.detach().requires_grad_(True)
    z5 = torch.add(z5, gradient5*learn_rate)
    if z5.norm()>1:
        z5 = torch.div(z5, z5.norm())    
    z5 = z5.detach().requires_grad_(True)
    z6 = torch.add(z6, gradient6*learn_rate)
    if z6.norm()>1:
        z6 = torch.div(z6, z6.norm())    
    z6 = z6.detach().requires_grad_(True)
    z7 = torch.add(z7, gradient7*learn_rate)
    if z7.norm()>1:
        z7 = torch.div(z7, z7.norm())    
    z7 = z7.detach().requires_grad_(True)
    z8 = torch.add(z8, gradient8*learn_rate)
    if z8.norm()>1:
        z8 = torch.div(z8, z8.norm())    
    z8 = z8.detach().requires_grad_(True)
    z9 = torch.add(z9, gradient9*learn_rate)
    if z9.norm()>1:
        z9 = torch.div(z9, z9.norm())    
    z9 = z9.detach().requires_grad_(True)
    voters = [z0, z1, z2, z3, z4, z5, z6, z7, z8, z9]

    trace_X.append(z8.detach().numpy()[0])
    trace_Y.append(z8.detach().numpy()[1])

    #fig, ax = plt.subplots()
    #fig.set_figheight(6)
    #fig.set_figwidth(6)
    #plt.xlabel("x-dimension")
    #plt.ylabel("y-dimension")
    
    Z = reward_z8(X, Y, z9.detach(), s8, s9, g0.detach(), g1.detach(), g2.detach(), s_voters, isRegularized)
    
    if (t>=steps-1):    
        fig = plt.figure(figsize = (24,16))
        plt.rc('axes', labelsize=32)    # fontsize of the x and y labels
        plt.imshow(Z, extent = [-1,1,-1,1], cmap = 'jet', alpha = 1)    
        
        plt.plot(trace_X, trace_Y)
        plt.plot(trace_X[-1], trace_Y[-1], '*', markersize=20, label = "reward of v9")
    
        plt.xlabel('x-dimension')
        plt.ylabel('y-dimension')
        plt.colorbar()
        plt.legend(loc = "upper right")
        plt.savefig('tmp_'+str(t+1)+'_'+label+'.png', dpi=500)
        plt.close()
    #print("\nFinal gradients: ")
    #print(gradient0, gradient1, gradient2, gradient3, gradient4, gradient5, gradient6, gradient7, gradient8, gradient9)

"""

#plt.show()
frames = []
for t in time:
    image = imageio.imread('tmp_'+str(t)+'_'+label+'.png')
    frames.append(image)
#frames.append('tmp_'+str(steps)+'_'+label+'.png')
imageio.mimsave('./party_formation_gradient_demo_'+label+'.gif', # output gif
                frames,          # array of input frames
                fps = 5) 

"""

"""
g1=(s1+s4)/2
g2=(s2+s3+s5)/3

ug1=torch.tensor([0.0])
ug2=torch.tensor([0.0])

for v in s_voters:
    ug1 += torch.inner(g1, v)
    ug2 += torch.inner(g2, v)
    
exp_ug_all = torch.exp(torch.tensor([2*ug1,3*ug2])).sum()     
    
pg1 = torch.exp(2*ug1)/exp_ug_all
pg2 = torch.exp(3*ug2)/exp_ug_all

r1 = pg1*torch.inner(g1,s1)+pg2*torch.inner(g2,s1)
r2 = pg1*torch.inner(g1,s2)+pg2*torch.inner(g2,s2)
r3 = pg1*torch.inner(g1,s3)+pg2*torch.inner(g2,s3)
r4 = pg1*torch.inner(g1,s4)+pg2*torch.inner(g2,s4)
r5 = pg1*torch.inner(g1,s5)+pg2*torch.inner(g2,s5)



g1=(z1+z4)/2
g2=(z2+z3+z5)/3
#g3=z5
#g4=z3

ug1=torch.tensor([0.0])
ug2=torch.tensor([0.0])
#ug3=torch.tensor([0.0])
#ug4=torch.tensor([0.0])

for v in s_voters:
    ug1 += torch.inner(g1, v)
    ug2 += torch.inner(g2, v)
    #ug3 += torch.inner(g3, v)
    #ug4 += torch.inner(g4, v)
    
exp_ug_all = torch.exp(torch.tensor([2*ug1,3*ug2])).sum()     
    
pg1 = torch.exp(2*ug1)/exp_ug_all
pg2 = torch.exp(3*ug2)/exp_ug_all
#pg3 = torch.exp(ug3)/exp_ug_all
#pg4 = torch.exp(ug4)/exp_ug_all

r1 = pg1*torch.inner(g1,s1)+pg2*torch.inner(g2,s1)#+pg3*torch.inner(g3,s1)#+pg4*torch.inner(g4,s1)
r2 = pg1*torch.inner(g1,s2)+pg2*torch.inner(g2,s2)#+pg3*torch.inner(g3,s2)#+pg4*torch.inner(g4,s2)
r3 = pg1*torch.inner(g1,s3)+pg2*torch.inner(g2,s3)#+pg3*torch.inner(g3,s3)#+pg4*torch.inner(g4,s3)
r4 = pg1*torch.inner(g1,s4)+pg2*torch.inner(g2,s4)#+pg3*torch.inner(g3,s4)#+pg4*torch.inner(g4,s4)
r5 = pg1*torch.inner(g1,s5)+pg2*torch.inner(g2,s5)#+pg3*torch.inner(g3,s5)#+pg4*torch.inner(g4,s5)

"""