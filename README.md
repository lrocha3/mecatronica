mecatronica
===========

This project uses a LDC100EVM sensor and a Roomba!

Note: LDC1000EVM in Stream Mode it gives 0x####,0x#### where the first hex number is the proximity and the second is the frequency.

It reads the data from the sensor and then i mark in rviz the position x, y, z of the mine.

Comandos necessários:

Listar portas --> dmesg | grep tty
Permissoes livres em todas as portas --> sudo chmod 777 /dev/tty*


Tuturial para executar:

Programa I:

roscore

rosrun sensor le_sensor treshold (int)

rosrun sensor recebe_dados


Programa II

roscore

roslaunch roomba_bringup roomba_555.launch

roslaunch sensor sensor.launch

rosrun sensor le_sensor treshold (int)

rosrun sensor points_sensor

roslaunch roomba_teleop keyboard_teleop.launch

rosrun rviz rviz

// Carregar modelo robot

// Carregar array markers


Testes I

roscore

rosrun sensor marca_minas

rosrun rviz rviz

// Carregar o array markers
