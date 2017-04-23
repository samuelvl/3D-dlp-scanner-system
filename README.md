# 3D DLP Scanner System

With **3D DLP high-speed scanner system** it is possible to retrieve the 3D shape of an object using a **DLP LightCrafter 4500 Projector** controlled by a **Raspberry Pi**, applying **DFP** (Digital Fringe Projection) techniques.

In a simple way, the system works as follows:

<p align="center">
  <img src="imgs/project_diagram.png">
</p>

The whole process is explained at **[this document](Project.pdf)**.

## Instruction Manual
If you just want to **test the system** you only need last MATLAB version to date (2017a version). Download **[matlab script](matlab)** and run algorithm.m which will display a 3D object representation as example.

If you want to **build the whole system** you will need:
- **[Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)** with last version of **[Raspbian Jessie lite](https://www.raspberrypi.org/downloads/raspbian/)** or similar installed.
- **[DLP LightCrafter 4500](http://www.ti.com/tool/dlplcr4500evm)**.
- MATLAB 2017a.
- Any camera, e.g. the **smartphone camera**.
