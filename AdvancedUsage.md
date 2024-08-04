## Problem formulation

Classic travelling salesman problem (TSP) formulation can be found [here](https://en.wikipedia.org/wiki/Travelling_salesman_problem).  
In Moving Target TSP (MTTSP) it's more convenient to talk about *preys* and *predators* instead of cities and travelling salesman. For my own convenience I'd say *yerps* instead of predators. By the problem formulation, preys move with constant direction and constant speed, which means that one should set its initial position and velocity vector to set a prey. Yerp need only initial point to be set.  
**Important note:** project supports only 1 or 2 yerps. Both of these yerps are totally equal, which means they have the same maximum velocity. Then, without loss of generality, yerps' maximum velocity can be set to 1. Therefore all preys' velocities should be less than 1 to be confident yerps can intercept all the preys at finite time.

All the preys have their ids (numbers like 0, 1, 2, etc...). Let's consider there only 3 preys and 1 yerp. So, a yerp should intercept all the yerps for the shortest possible time. He can firstly intercept prey #0, then #1, then #2, which will take certain time to do this. He has only six interception orders: 012, 021, 102, 120, 201, 210, the best one is the fastest one, i.e. interception order which will take the shortest time.

The task is to find the time-optimal order of interception and of course the resulted time. Everything stays the same if there is more than 3 preys. Two yerps implies that orders will look like 20;13: the first yerp should intercept preys in order 20, the second one -- 13.

The GUI solves this problem with up to 20 preys and 1 yerp or with up to 14 preys and 2 yerps. More take too much time for the computation (depends on processor).

## Advanced GUI usage

* Instead of clicking on any action on the menu you can use shortcuts
* You can *save* configuration to .txt file or *load* it from the .txt file
* *Restart* action clears the scene
* *Undo* action (Ctrl+Z) works in Construction mode and undo the previous action, which is one of the follows: prey start set, prey direction set, prey velocity set, yerp start set. This may be useful if user misclicks at some time and doesn't want to refresh the whole scene
* Mouse scroll causes scene's zoom and WASD causes scene's translation
* *Default Scene View* action undo all made zoom and scene's translations
* If you will press Shift while prey's direction setting then the direction will be fully horizontal or vertical
* You can *speed up* the animation (Up arrow key) x2, x5, x10. The next speed up usage will get the animation speed back to the default
* Z key is extremely useful. It sets the scene (via zoom and translation) to make all the preys and yerps visible (not being out of scene boundaries)
* In animation mode you can set the time moment not only via timeline but via directly inputing it from keyboard
* After Animation mode you are still able to switch to the Construction one to edit the configuration
* You can use *Use plan* action if you want not to compute the optimal one but just to know the resulted time of a certain plan or to watch the animation of this plan. It could be useful e.g. with 2 yerps and more than 14 preys.
* *Use Best Plan* action will paste back the optimal interception plan so you don't need to restart the whole computation if you forget it
* You can generate configuration randomly (G), all the entities will be inside the blue sided rectangle. You can change its size via mouse drag
* Control Panel or may be better Info Panel (I) provides some *general info* and *random generation* settings. *Preys from 1 to 20* means random amount of preys, the same is with yerps, but also you can uncheck these options and input prey/yerp amount manually. *Set all Yerps to zero* option implies that all the yerps will be spawned at zero.
* *General Info* in Construction Mode. It contains of two tables dedicated to yerps and preys. You can find there initial data of yerps (initial position) and preys (initial positions, direction and velocity). All of these parameters can be edited via double-click on the table's cell you want to edit. Click on the written in blue prey number to highlight chosen prey (to distinguish it from others)
* *General Info* in Animation Mode. Yerp's table. Yerps table shows optimal interception order for every yerp and written in blue time of this interception realization. Click on it to set time on the timeline to clicked value. Also there is rows with \* symbol in yerp's table, 0\* or 1\*. 0\* row responses to the same configuration but only with the first yerp (w/o the second one) and the 1\* row responses to the same configuration but only with the second yerp (w\o the first one). As yerps could be spawned in different initial positions, working times on 0\* and 1\* can be different
* *General Info* in Animation Mode. Prey's table. All the preys are sorted now by their interception time moments. *Died* column represent these moments. Click on it to set time on the timeline to clicked value. *Yerp* column represent which yerp intercepts prey you are looking at. *DieX* and *DieY* shows the position of interception
