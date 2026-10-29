import turtle
from turtle import *
m = 15
screensize(1000, 1000)
setheading(90)
speed(0)
tracer(0)

down()
for x in range(8):
    rt(45)
    fd(8*m)

up()

for x in range(-60,60):
    for y in range(-60, 60):
        goto(x*m, y*m)
        dot(3, 'red')

mainloop()