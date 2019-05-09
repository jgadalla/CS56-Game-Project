Sixth Street Scramble

Created by Barkot Efuye, Justin Gadalla, Herve Iradukunda, and Clint Isom

Our game is a top down traffic simulator, where the user is given control over a busy intersection. Cars are constantly approaching the intersection, and like any good driver, they always stop to look for pedestrians. However, it is up to you to decide when it is safe for the cars to go. By pressing either W,A,S, or D, you tell the car stopped at the intersection in their respective lanes that they can accelerate, and off they go! Hurry up though, there are cars fast approaching from behind as well as other lanes of traffic to watch out for!

Compilation Instructions:
clang++ -std=c++11 *.cpp -F /Library/Frameworks/ -framework SDL2 -framework SDL2_image
Run Executable:
./a.out

Provided below is a link to our YouTube channel:
https://www.youtube.com/channel/UCLSdcJS5Yw2Xm9ryT_l5iyw

GitHub Overview:

Code - Contains all of our code for the game
Images - Contains any images used in our code/game, also contains our team photo
Organization/Planning - Contains documents used to details our planning/organization of this project

Our game design meets all of the project requirements. First, the polymorphism aspect is met with the inclusion of different types of units. Cars, trucks and semi's all inherit from the Unit Class.

The two design patterns we used in our programming was object oriented design and agile development. We created our game around our objects such as our units, queues,textures, and brought them all together in our main function. As for the agile programming, our progress videos demonstrate how we initially created a very basic version of our game, a sprint, and continually developed that over time. This allowed us to make continual progress on our game while making it clear what the next steps were in its creation. 

Our game takes in input files of pngs, and is able to convert them to textures to be utilized in our game. 

We also overload many functions in our game, including the render functions and move functions. We also note what memory we allocated on the heap, and took steps to ensure that it was all released by the end of it. 

There were many features we wanted to implement, such as sound, bicycles, and power ups. We were also never able to implement our options button, so it does nothing when it is clicked on. However, due to time, we were unable to implement them, but in the future we would love to explore the possibilities of how to make our game the best it can be. 

*Note*: Herve was not present for the (last minute) taking of our team photo, we apologize for that failure in team planning.
