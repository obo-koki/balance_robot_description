# balance_robot_description
![balance_robot](https://user-images.githubusercontent.com/60743930/104920146-b5a27e80-59da-11eb-8a1b-30fabd63d69b.png)
## 立ち上げ
gazebo+rviz   
```roslaunch balance_robot_description balance_robot_with_empty_world.launch```

rvizのみ   
```roslaunch balance_robot_description robot_display_simple_sim.launch```


## コントローラの変更
```/balance_robot_description/launch/balance_robot_with_empty_world.launch``` の29行目   
```<include file="$(find balance_robot_description)/launch/robot_control_diff.launch"/>```
のインクルード先を所望のコントローラに変更
