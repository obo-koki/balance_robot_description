# Balance Robot Description
倒立振子移動ロボットのシミュレーション
![balance_robot](https://user-images.githubusercontent.com/60743930/104920146-b5a27e80-59da-11eb-8a1b-30fabd63d69b.png)
<<<<<<< HEAD

# Usage

１，balance_robotdescription/script/robot_param.yaml にロボットのパラメータを保存

２，フィードバックゲインを算出するスクリプトを実行
```
$ cd balance_robot_description/script
$ python get_control_gain.py
```
３、ロボットのシミュレーション立ち上げ
```
roslaunch balance_robot_description robot_control_sim.launch
```

# Reference

実機用プログラム
https://github.com/obo-koki/balance_robot_control.git
=======
## 立ち上げ
gazebo+rviz   
```roslaunch balance_robot_description balance_robot_with_empty_world.launch```

rvizのみ   
```roslaunch balance_robot_description robot_display_simple_sim.launch```


## コントローラの変更
```/balance_robot_description/launch/balance_robot_with_empty_world.launch``` の29行目   
```<include file="$(find balance_robot_description)/launch/robot_control_diff.launch"/>```
のインクルード先を所望のコントローラに変更
>>>>>>> simplemodel
