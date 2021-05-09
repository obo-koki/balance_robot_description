# Balance Robot Description
倒立振子移動ロボットのシミュレーション
![balance_robot](https://user-images.githubusercontent.com/60743930/104920146-b5a27e80-59da-11eb-8a1b-30fabd63d69b.png)

## Installation
diff_drive_controller_effort

https://github.com/obo-koki/diff_drive_controller_effort

bobble_controllers

https://github.com/obo-koki/bobble_controllers
※branchをbalance_robotに変更すること

## Usage
### １．ロボットパラメータ
balance_robotdescription/script/robot_param.yaml にロボットのパラメータを保存

### ２．フィードバックゲインを算出するスクリプトを実行
```
$ cd balance_robot_description/script
$ python get_control_gain.py
```
### ３．シミュレータ立ち上げ   
#### 自作プログラム 
gazebo + rviz
```
roslaunch balance_robot_description sim.launch
```
rvizのみ   
```
roslaunch balance_robot_description robot_display_simple_sim.launch
```
#### 参考プログラム(bobble)
gazebo
```
roslaunch balance_robot_description bobble_sim.launch
```

### ４. コントローラ起動
#### 自作プログラム
```
roslaunch balance_robot_description control.launch
```
#### 参考プログラム(bobble)
```
roslaunch balance_robot_description bobble_control.launch
```

## Reference

実機用プログラム

https://github.com/obo-koki/balance_robot_control.git

参考プログラム(bobble_controllers)

https://github.com/super-owesome/bobble_controllers