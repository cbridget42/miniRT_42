# miniRT_42
project for ecole 42  
  
This project is an introduction to the beautiful world of Raytracing.  
Once completed you will be able to render simple Computer-Generated-Images and you  
will never be afraid of implementing mathematical formulas again.  
You can read about ray tracing [here](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))  
  
### Requirements:
* Mandatory part:  
  + You need at least these 3 simple geometric objects: plane, sphere, cylinder.  
  + If applicable, all possible intersections and the inside of the object must be handled  
    correctly.  
  + Your program must be able to resize the object’s unique properties: diameter for a  
    sphere and the width and height for a cylinder.  
  + Your program must be able to apply translation and rotation transformation to  
    objects, lights and cameras (except for spheres and lights that cannot be rotated).  
  + Light management: spot brightness, hard shadows, ambiance lighting (objects are  
    never completely in the dark). You must implement Ambient and diffuse lighting.  
* bonus part:  
  + Add specular reflection to have a full Phong reflection model.  
  + Colored and multi-spot lights.  
  
You can see the full assignment here [subject](https://github.com/cbridget42/miniRT_42/blob/main/subject/en.subject.pdf)  
Coding style: [norminette](https://github.com/cbridget42/miniRT_42/blob/main/subject/en.norm.pdf)  
  
### Usage:
* You need to download the repository and compile the code! To do this, run:
	```bash
	git clone git@github.com:cbridget42/miniRT_42.git
	cd miniRT_42
	make
	or
	make bonus//if you want to compile with bonus
	```
* then you will have a miniRT file. Exemple usage:
	```bash
	./miniRT [.rt file with your scene]
	```
  
	```bash
	./miniRT scenes/bonus/scene_mirror_ocean.rt
	```
* also you can:
	```bash
	make clean //remove objects files
	make fclean //remove objects files and miniRT
	```
  
### Keyboard shortcuts
<table width="100%">
<thead>
<tr>
<td width="65%" height="60px" align="center" cellpadding="0">
<strong>Description</strong>
</td>
<td width="10%" align="center" cellpadding="0">
<span style="width:70px">&nbsp;</span><strong>Key</strong><span style="width:50px">&nbsp;</span>
</td>
</tr>
</thead>
<tbody>
<tr>
<td valign="top" height="30px">change the way you control</td>
<td valign="top" align="center"><kbd>&nbsp;q&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">select object</td>
<td valign="top" align="center"><kbd>&nbsp;e&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">move</td>
<td valign="top" align="center"><kbd>&nbsp;▲&nbsp;</kbd><kbd>&nbsp;▼&nbsp;</kbd><kbd>&nbsp;a&nbsp;</kbd><kbd>&nbsp;d&nbsp;</kbd><kbd>&nbsp;w&nbsp;</kbd><kbd>&nbsp;s&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">change radius</td>
<td valign="top" align="center"><kbd>&nbsp;z&nbsp;</kbd><kbd>&nbsp;x&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">change hight</td>
<td valign="top" align="center"><kbd>&nbsp;c&nbsp;</kbd><kbd>&nbsp;v&nbsp;</kbd></td>
</tr>
<tr>
</tbody>
</table>
  
### ScreenShots:
![image](https://github.com/cbridget42/miniRT_42/blob/main/images/Screenshot%20from%202022-11-17%2013-10-47.png)
![image](https://github.com/cbridget42/miniRT_42/blob/main/images/Screenshot%20from%202022-11-17%2023-28-49.png)
![image](https://github.com/cbridget42/miniRT_42/blob/main/images/Screenshot%20from%202022-11-17%2013-15-03.png)
![image](https://github.com/cbridget42/miniRT_42/blob/main/images/Screenshot%20from%202022-11-17%2013-13-09.png)
  