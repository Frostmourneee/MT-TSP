# Qt GUI to investigate 2D Moving Target Travelling Salesman Problem (MTTSP)

## A project to play around a well-famous optimization problem, TSP, and mainly its generalization: TSP with moving targets
This project provides the user-friendly GUI to construct different MTTSP configurations with 1 or 2 travellers, to calculate the time-optimal solutions to them and to demonstrate the whole interception process via animation.
The main purpose of the project is not to propose the fastest solving algorithm but to create a visually-informative animation of the MTTSP. Thus, this project can be used for eye-pleasant demonstrations, not only for high science :)

## Basic usage
It's convenient here to talk about *preys* and *predators*, so preys move along their straight lines and predators should catch (intercept) them for the shortest possible time. A predator will be called *yerp* further (prey -> yerp). Via this GUI you can

* Create yerp or prey just via mouse click on the canvas (coordinate grid)
* Choose a prey's velocity vector via mouse moving
* Use random generation for preys and yerps instead of mouse
* Save or load the configuration from .txt file so you can comfortably share it
* Calculate the time-fastest interception order for yerps in provided configuration
* View the animation of how yerps catch preys over time
* Zoom or translate the scene in animation mode
* Play, pause or speed up the animation or use the timeline like in the yt videos
* View the animation not of the optimal interception order but of the manually specified

[<img width="300" alt="1" src="https://github.com/user-attachments/assets/a2b153f7-f8d8-43c0-9432-f61a2c2aebc6">](https://www.youtube.com/watch?v=NIMdXV8T8XY)   [<img width="300" alt="2" src="https://github.com/user-attachments/assets/1da1f86e-186b-48b5-b637-0ca116147a91">](https://www.youtube.com/watch?v=r9TA_sKBvik)

Look into [Advanced](https://github.com/Frostmourneee/MT-TSP/blob/main/AdvancedUsage.md) to get more!

## How to 4 common users
Download the first .zip archive from the [latest release](https://github.com/Frostmourneee/MT-TSP/releases), unpack it to some folder and launch MT-TSP.exe  

## How to 4 contributors
Take into account that the project was made via Qt v5.14.2.

Open Qt Creator, File --> New File or Project --> Import Project --> Git Clone. Paste https://github.com/Frostmourneee/MT-TSP.git into "Repository" and choose path you want.  
To make icons work properly turn off "Shadow build" (google how to if needed)

## Keywords
Moving target travelling salesman problem, MTTSP animated demonstration, Preys and predators, UAV optimal interception, Interception problem, Travelling salesman problem, Optimization problem, Combinatorial problem
