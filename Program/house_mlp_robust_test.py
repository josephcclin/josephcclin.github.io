# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import pandas as pd
import numpy as np
#from sklearn.compose import ColumnTransformer
#from sklearn.pipeline import Pipeline
#from sklearn.impute import SimpleImputer
#from sklearn.preprocessing import StandardScaler, OneHotEncoder
#from sklearn.svm import NuSVR
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error 
#from sklearn.neural_network import MLPRegressor
from joblib import load#, dump
#from sklearn.ensemble import VotingRegressor

num_iter = 100

input_data  = '2016A_lvr_land_A_converted.csv'
df_input = pd.read_csv(input_data , header=[0])
df_input['time_diff'] = pd.to_datetime(df_input['交易年月日_date']) -pd.to_datetime(df_input['建築完成年月_date'])
df_input['time_diff'] = df_input['time_diff'] / np.timedelta64(1,'D')
df_input['time_diff'].fillna(0, inplace=True)

# 預售屋
df_input['pre-sold'] = df_input['備註'].str.contains('預售').fillna(False)*1

# 特殊關係
df_input['relatives'] = df_input['備註'].str.contains('特殊關係|二親等|二等親|母女|姊弟').fillna(False)*1

#含增建
df_input['additional_construction'] = df_input['備註'].str.contains('增建').fillna(False)*1

# Calculate the average space of rooms
df_input['total_rooms'] = df_input['建物現況格局-廳']+df_input['建物現況格局-房']+df_input['建物現況格局-衛']
df_input['total_rooms'] = df_input['total_rooms'].replace(0,1)
df_input['mean_space'] = df_input['建物移轉總面積平方公尺']/(df_input['total_rooms'])

df_input['移轉層次_num'] = df_input['移轉層次_num'].fillna(0)
transfer_floors = np.array(list(df_input['移轉層次_num']))
total_floors =  np.array(df_input['總樓層數_num'])
transfer_floors_list = transfer_floors
transfer_floors_list = [list(np.arange(total_floors[i])) if transfer_floors[i] == 0 else list(np.fromstring(transfer_floors[i], dtype=int, sep=',')) for i in range(total_floors.shape[0]) ]
transfer_floors_count = [len(transfer_floors_list[i]) for i in range(len(transfer_floors_list))]

df_input['transfer_floors_list'] = transfer_floors_list 
df_input['transfer_floors_count'] = transfer_floors_count 

UNLUCKY_CHECK = [1 if 4 in transfer_floors_list[i] or 10 in transfer_floors_list[i] else 0 for i in range(len(transfer_floors_list))]
LOWER_FLOORS_CHECK = [1 if 1 in transfer_floors_list[i] or 2 in transfer_floors_list[i] else 0 for i in range(len(transfer_floors_list))]

df_input['IS_UNLUCKY'] = UNLUCKY_CHECK
df_input['IS_LOWER'] = LOWER_FLOORS_CHECK

df_input_clean = df_input[df_input['單價每平方公尺'] > 0]
df_input_car_clean = df_input_clean[df_input_clean['車位_num'] > 0]
#df_input_no_car_clean = df_input_clean[df_input_clean['車位_num'] == 0]

# Get the initial features
FtsInput = df_input_clean[['主要建材_cat', '主要用途_cat', '全移轉_bin', 'time_diff', '土地_num', '土地移轉總面積平方公尺', 
                     '建物_num', '建物型態_cat', '建物現況格局-廳', '建物現況格局-房', '建物現況格局-衛'	, '建物現況格局-隔間_bin',	
                     '建物移轉總面積平方公尺', '有無管理組織_bin', 'transfer_floors_count', '車位_num', '車位移轉總面積平方公尺', 
                     '車位類別_cat', '都市土地使用分區_cat', '鄉鎮市區_cat', 'IS_UNLUCKY', 'IS_LOWER', 'mean_space', 
                     'pre-sold', 'relatives', 'additional_construction']]

FtsInputCar = df_input_car_clean[['主要建材_cat', '主要用途_cat', '全移轉_bin', 'time_diff', '土地_num', '土地移轉總面積平方公尺', 
                     '建物_num', '建物型態_cat', '建物現況格局-廳', '建物現況格局-房', '建物現況格局-衛'	, '建物現況格局-隔間_bin',	
                     '建物移轉總面積平方公尺', '有無管理組織_bin', 'transfer_floors_count', '車位_num', '車位移轉總面積平方公尺', 
                     '車位類別_cat', '都市土地使用分區_cat', '鄉鎮市區_cat', 'IS_UNLUCKY', 'IS_LOWER', 'mean_space', 
                     'pre-sold', 'relatives', 'additional_construction']]
'''
FtsInputNoCar = df_input_no_car_clean[['主要建材_cat', '主要用途_cat', '全移轉_bin', 'time_diff', '土地_num', '土地移轉總面積平方公尺', 
                     '建物_num', '建物型態_cat', '建物現況格局-廳', '建物現況格局-房', '建物現況格局-衛'	, '建物現況格局-隔間_bin',	
                     '建物移轉總面積平方公尺', '有無管理組織_bin', 'transfer_floors_count', '都市土地使用分區_cat', '鄉鎮市區_cat', 
                     'IS_UNLUCKY', 'IS_LOWER',  'mean_space', 'pre-sold', 'relatives', 'additional_construction']]
'''

FtsValue = np.log(df_input_clean['總價元'] + df_input_clean['車位總價元'])
FtsValueCar = np.log(df_input_car_clean['總價元'] + df_input_car_clean['車位總價元'])
#FtsValueNoCar = np.log(df_input_no_car_clean['總價元'])

categorical_features = ['主要建材_cat', '主要用途_cat', '建物型態_cat', '車位類別_cat', '都市土地使用分區_cat', '鄉鎮市區_cat']
numeric_features = ['全移轉_bin', 'time_diff', '土地_num', '土地移轉總面積平方公尺', '建物_num', 
                      '建物現況格局-廳', '建物現況格局-房', '建物現況格局-衛'	, '建物現況格局-隔間_bin',	
                     '建物移轉總面積平方公尺', '有無管理組織_bin', '車位_num', '車位移轉總面積平方公尺', 
                     'IS_UNLUCKY', 'IS_LOWER',  'mean_space']

'''
NoCar_categorical_features = ['主要建材_cat', '主要用途_cat', '建物型態_cat', '都市土地使用分區_cat', '鄉鎮市區_cat']
NoCar_numeric_features = ['全移轉_bin', 'time_diff', '土地_num', '土地移轉總面積平方公尺', '建物_num', 
                      '建物現況格局-廳', '建物現況格局-房', '建物現況格局-衛'	, '建物現況格局-隔間_bin',	
                     '建物移轉總面積平方公尺', '有無管理組織_bin', 'IS_UNLUCKY', 'IS_LOWER',  'mean_space']
'''

# split the data into the training set and the test set 
X_train, X_test, y_train, y_test = train_test_split(FtsInput, FtsValue, test_size=0.1, random_state=0)
X_train_c, X_test_c, y_train_c, y_test_c = train_test_split(FtsInputCar, FtsValueCar, test_size=0.1, random_state=0)
#X_train_nc, X_test_nc, y_train_nc, y_test_nc = train_test_split(FtsInputNoCar, FtsValueNoCar, test_size=0.1, random_state=0)

pred_list = []
pred_list_c = []
#pred_list_nc = []

train_pred_list = []
train_pred_list_c = []
#train_pred_list_nc = []

for iteration in range(num_iter):    
    rgn = load('layer4/tot_model'+str(iteration)+'.joblib')
    rgn_c = load('layer4/car_model'+str(iteration)+'.joblib')
    #rgn_nc = load('layer4/nocar_model'+str(iteration)+'.joblib')
        
    y_pred = rgn.predict(X_test)
    y_pred_train = rgn.predict(X_train)
    
    y_pred_c = rgn_c.predict(X_test_c)
    y_pred_train_c = rgn_c.predict(X_train_c)
    
    #y_pred_nc = rgn_nc.predict(X_test_nc)
    #y_pred_train_nc = rgn_nc.predict(X_train_nc)
    
    pred_list.append(y_pred)
    pred_list_c.append(y_pred_c)
    #pred_list_nc.append(y_pred_nc)
    
    train_pred_list.append(y_pred_train)
    train_pred_list_c.append(y_pred_train_c)
    #train_pred_list_nc.append(y_pred_train_nc)
    
y_pred_avg = np.array(pred_list).mean(axis=0)
y_pred_train_avg = np.array(train_pred_list).mean(axis=0)
y_pred_c_avg = np.array(pred_list_c).mean(axis=0)
y_pred_train_c_avg = np.array(train_pred_list_c).mean(axis=0)
#y_pred_nc_avg = np.array(pred_list_nc).mean(axis=0)
#y_pred_train_nc_avg = np.array(train_pred_list_nc).mean(axis=0)
    
print('#Overal result:')
print('RMSE: %f' %(np.sqrt(mean_squared_error(y_pred_avg, y_test))))
print('RMSE (train): %f\n' %(np.sqrt(mean_squared_error(y_pred_train_avg, y_train))))

print('#Result of objects with parking lots:')
print('RMSE: %f' %(np.sqrt(mean_squared_error(y_pred_c_avg, y_test_c))))
print('RMSE (train): %f\n' %(np.sqrt(mean_squared_error(y_pred_train_c_avg, y_train_c))))
'''
print('#Result of objects with NO parking lots:')
print('RMSE: %f' %(np.sqrt(mean_squared_error(y_pred_nc_avg, y_test_nc))))
print('RMSE (train): %f' %(np.sqrt(mean_squared_error(y_pred_train_nc_avg, y_train_nc))))
   '''     
