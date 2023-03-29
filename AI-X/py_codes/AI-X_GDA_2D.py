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



learn_rate = torch.tensor(0.1)
steps = 100
time = list(np.arange(steps))

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


"""
u0 = torch.tensor([0.0])
u1 = torch.tensor([0.0])
u2 = torch.tensor([0.0])
u3 = torch.tensor([0.0])
u4 = torch.tensor([0.0])
u5 = torch.tensor([0.0])
u6 = torch.tensor([0.0])
u7 = torch.tensor([0.0])
u8 = torch.tensor([0.0])
u9 = torch.tensor([0.0])


for v in s_voters:
    u0 += torch.inner(z0, v)
    u1 += torch.inner(z1, v)
    u2 += torch.inner(z2, v)
    u3 += torch.inner(z3, v)
    u4 += torch.inner(z4, v)
    u5 += torch.inner(z5, v)
    u6 += torch.inner(z6, v)
    u7 += torch.inner(z7, v)
    u8 += torch.inner(z8, v)
    u9 += torch.inner(z9, v)
    
exp_u_all = torch.exp(torch.tensor([u0,u1,u2,u3,u4,u5,u6,u7,u8,u9])).sum()    

p0 = torch.exp(u0)/exp_u_all
p1 = torch.exp(u1)/exp_u_all
p2 = torch.exp(u2)/exp_u_all
p3 = torch.exp(u3)/exp_u_all
p4 = torch.exp(u4)/exp_u_all
p5 = torch.exp(u5)/exp_u_all
p6 = torch.exp(u6)/exp_u_all
p7 = torch.exp(u7)/exp_u_all
p8 = torch.exp(u8)/exp_u_all
p9 = torch.exp(u9)/exp_u_all


r0 = p0*torch.inner(z0,s0)+p1*torch.inner(z1,s0)+p2*torch.inner(z2,s0)+p3*torch.inner(z3,s0)+p4*torch.inner(z4,s0)+p5*torch.inner(z5,s0)+p6*torch.inner(z6,s0)+p7*torch.inner(z7,s0)+p8*torch.inner(z8,s0)+p9*torch.inner(z9,s0)
r1 = p0*torch.inner(z0,s1)+p1*torch.inner(z1,s1)+p2*torch.inner(z2,s1)+p3*torch.inner(z3,s1)+p4*torch.inner(z4,s1)+p5*torch.inner(z5,s1)+p6*torch.inner(z6,s1)+p7*torch.inner(z7,s1)+p8*torch.inner(z8,s1)+p9*torch.inner(z9,s1)
r2 = p0*torch.inner(z0,s2)+p1*torch.inner(z1,s2)+p2*torch.inner(z2,s2)+p3*torch.inner(z3,s2)+p4*torch.inner(z4,s2)+p5*torch.inner(z5,s2)+p6*torch.inner(z6,s2)+p7*torch.inner(z7,s2)+p8*torch.inner(z8,s2)+p9*torch.inner(z9,s2)
r3 = p0*torch.inner(z0,s3)+p1*torch.inner(z1,s3)+p2*torch.inner(z2,s3)+p3*torch.inner(z3,s3)+p4*torch.inner(z4,s3)+p5*torch.inner(z5,s3)+p6*torch.inner(z6,s3)+p7*torch.inner(z7,s3)+p8*torch.inner(z8,s3)+p9*torch.inner(z9,s3)
r4 = p0*torch.inner(z0,s4)+p1*torch.inner(z1,s4)+p2*torch.inner(z2,s4)+p3*torch.inner(z3,s4)+p4*torch.inner(z4,s4)+p5*torch.inner(z5,s4)+p6*torch.inner(z6,s4)+p7*torch.inner(z7,s4)+p8*torch.inner(z8,s4)+p9*torch.inner(z9,s4)
r5 = p0*torch.inner(z0,s5)+p1*torch.inner(z1,s5)+p2*torch.inner(z2,s5)+p3*torch.inner(z3,s5)+p4*torch.inner(z4,s5)+p5*torch.inner(z5,s5)+p6*torch.inner(z6,s5)+p7*torch.inner(z7,s5)+p8*torch.inner(z8,s5)+p9*torch.inner(z9,s5)
r6 = p0*torch.inner(z0,s6)+p1*torch.inner(z1,s6)+p2*torch.inner(z2,s6)+p3*torch.inner(z3,s6)+p4*torch.inner(z4,s6)+p5*torch.inner(z5,s6)+p6*torch.inner(z6,s6)+p7*torch.inner(z7,s6)+p8*torch.inner(z8,s6)+p9*torch.inner(z9,s6)
r7 = p0*torch.inner(z0,s7)+p1*torch.inner(z1,s7)+p2*torch.inner(z2,s7)+p3*torch.inner(z3,s7)+p4*torch.inner(z4,s7)+p5*torch.inner(z5,s7)+p6*torch.inner(z6,s7)+p7*torch.inner(z7,s7)+p8*torch.inner(z8,s7)+p9*torch.inner(z9,s7)
r8 = p0*torch.inner(z0,s8)+p1*torch.inner(z1,s8)+p2*torch.inner(z2,s8)+p3*torch.inner(z3,s8)+p4*torch.inner(z4,s8)+p5*torch.inner(z5,s8)+p6*torch.inner(z6,s8)+p7*torch.inner(z7,s8)+p8*torch.inner(z8,s8)+p9*torch.inner(z9,s8)
r9 = p0*torch.inner(z0,s9)+p1*torch.inner(z1,s9)+p2*torch.inner(z2,s9)+p3*torch.inner(z3,s9)+p4*torch.inner(z4,s9)+p5*torch.inner(z5,s9)+p6*torch.inner(z6,s9)+p7*torch.inner(z7,s9)+p8*torch.inner(z8,s9)+p9*torch.inner(z9,s9)


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
"""


for t in range(steps):
    u0 = torch.tensor([0.0])
    u1 = torch.tensor([0.0])
    u2 = torch.tensor([0.0])
    u3 = torch.tensor([0.0])
    u4 = torch.tensor([0.0])
    u5 = torch.tensor([0.0])
    u6 = torch.tensor([0.0])
    u7 = torch.tensor([0.0])
    u8 = torch.tensor([0.0])
    u9 = torch.tensor([0.0])


    for v in s_voters:
        u0 += torch.inner(z0, v)
        u1 += torch.inner(z1, v)
        u2 += torch.inner(z2, v)
        u3 += torch.inner(z3, v)
        u4 += torch.inner(z4, v)
        u5 += torch.inner(z5, v)
        u6 += torch.inner(z6, v)
        u7 += torch.inner(z7, v)
        u8 += torch.inner(z8, v)
        u9 += torch.inner(z9, v)
        
    exp_u_all = torch.exp(torch.tensor([u0,u1,u2,u3,u4,u5,u6,u7,u8,u9])).sum()    

    p0 = torch.exp(u0)/exp_u_all
    p1 = torch.exp(u1)/exp_u_all
    p2 = torch.exp(u2)/exp_u_all
    p3 = torch.exp(u3)/exp_u_all
    p4 = torch.exp(u4)/exp_u_all
    p5 = torch.exp(u5)/exp_u_all
    p6 = torch.exp(u6)/exp_u_all
    p7 = torch.exp(u7)/exp_u_all
    p8 = torch.exp(u8)/exp_u_all
    p9 = torch.exp(u9)/exp_u_all


    r0 = p0*torch.inner(z0,s0)+p1*torch.inner(z1,s0)+p2*torch.inner(z2,s0)+p3*torch.inner(z3,s0)+p4*torch.inner(z4,s0)+p5*torch.inner(z5,s0)+p6*torch.inner(z6,s0)+p7*torch.inner(z7,s0)+p8*torch.inner(z8,s0)+p9*torch.inner(z9,s0)
    r1 = p0*torch.inner(z0,s1)+p1*torch.inner(z1,s1)+p2*torch.inner(z2,s1)+p3*torch.inner(z3,s1)+p4*torch.inner(z4,s1)+p5*torch.inner(z5,s1)+p6*torch.inner(z6,s1)+p7*torch.inner(z7,s1)+p8*torch.inner(z8,s1)+p9*torch.inner(z9,s1)
    r2 = p0*torch.inner(z0,s2)+p1*torch.inner(z1,s2)+p2*torch.inner(z2,s2)+p3*torch.inner(z3,s2)+p4*torch.inner(z4,s2)+p5*torch.inner(z5,s2)+p6*torch.inner(z6,s2)+p7*torch.inner(z7,s2)+p8*torch.inner(z8,s2)+p9*torch.inner(z9,s2)
    r3 = p0*torch.inner(z0,s3)+p1*torch.inner(z1,s3)+p2*torch.inner(z2,s3)+p3*torch.inner(z3,s3)+p4*torch.inner(z4,s3)+p5*torch.inner(z5,s3)+p6*torch.inner(z6,s3)+p7*torch.inner(z7,s3)+p8*torch.inner(z8,s3)+p9*torch.inner(z9,s3)
    r4 = p0*torch.inner(z0,s4)+p1*torch.inner(z1,s4)+p2*torch.inner(z2,s4)+p3*torch.inner(z3,s4)+p4*torch.inner(z4,s4)+p5*torch.inner(z5,s4)+p6*torch.inner(z6,s4)+p7*torch.inner(z7,s4)+p8*torch.inner(z8,s4)+p9*torch.inner(z9,s4)
    r5 = p0*torch.inner(z0,s5)+p1*torch.inner(z1,s5)+p2*torch.inner(z2,s5)+p3*torch.inner(z3,s5)+p4*torch.inner(z4,s5)+p5*torch.inner(z5,s5)+p6*torch.inner(z6,s5)+p7*torch.inner(z7,s5)+p8*torch.inner(z8,s5)+p9*torch.inner(z9,s5)
    r6 = p0*torch.inner(z0,s6)+p1*torch.inner(z1,s6)+p2*torch.inner(z2,s6)+p3*torch.inner(z3,s6)+p4*torch.inner(z4,s6)+p5*torch.inner(z5,s6)+p6*torch.inner(z6,s6)+p7*torch.inner(z7,s6)+p8*torch.inner(z8,s6)+p9*torch.inner(z9,s6)
    r7 = p0*torch.inner(z0,s7)+p1*torch.inner(z1,s7)+p2*torch.inner(z2,s7)+p3*torch.inner(z3,s7)+p4*torch.inner(z4,s7)+p5*torch.inner(z5,s7)+p6*torch.inner(z6,s7)+p7*torch.inner(z7,s7)+p8*torch.inner(z8,s7)+p9*torch.inner(z9,s7)
    r8 = p0*torch.inner(z0,s8)+p1*torch.inner(z1,s8)+p2*torch.inner(z2,s8)+p3*torch.inner(z3,s8)+p4*torch.inner(z4,s8)+p5*torch.inner(z5,s8)+p6*torch.inner(z6,s8)+p7*torch.inner(z7,s8)+p8*torch.inner(z8,s8)+p9*torch.inner(z9,s8)
    r9 = p0*torch.inner(z0,s9)+p1*torch.inner(z1,s9)+p2*torch.inner(z2,s9)+p3*torch.inner(z3,s9)+p4*torch.inner(z4,s9)+p5*torch.inner(z5,s9)+p6*torch.inner(z6,s9)+p7*torch.inner(z7,s9)+p8*torch.inner(z8,s9)+p9*torch.inner(z9,s9)

    '''
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
    '''
    
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

    fig, ax = plt.subplots()
    #fig.set_figheight(6)
    #fig.set_figwidth(6)
    plt.xlabel("x-dimension")
    plt.ylabel("y-dimension")
    X = np.array([voters[i].detach().numpy()[0] for i in range(10)])
    Y = np.array([voters[i].detach().numpy()[1] for i in range(10)])
    labels = ["v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10"]
    colors = cm.rainbow(np.linspace(0, 1, len(labels)))
    ax.scatter(X, Y, s=50, c=colors)
    for i, label in enumerate(labels):
        ax.annotate(label, (X[i], Y[i]), fontsize=10, va="top", ha="left")
        
    plt.savefig('tmp_'+str(t)+'.png')
    plt.close()
    #print("\nFinal gradients: ")
    #print(gradient0, gradient1, gradient2, gradient3, gradient4, gradient5, gradient6, gradient7, gradient8, gradient9)

#plt.show()
frames = []
for t in time:
    image = imageio.v2.imread('tmp_'+str(t)+'.png')
    frames.append(image)

imageio.mimsave('./party_formation_demo_individuals.gif', # output gif
                frames,          # array of input frames
                fps = 5) 

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