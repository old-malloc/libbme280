<h1 class="western">
IOT Lab – Data Acquisition</h1>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>
<font face="Liberation Sans, sans-serif"><font size="4" style="font-size: 10pt">Vittorino
Baldi (vittorino.baldi@gmail.com)</font></font>
</p>
<p style="margin-bottom: 0cm; line-height: 100%">
This series of articles are intended to be an explanatory exposition
useful for understanding the general principles of operation of IOT
(Internet Of Things) solutions.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">This will be done
with the goal of creating a simple laboratory prototype for measuring
environmental parameters (temperature, humidity and pressure) by
identifying the hardware and software components necessary to meet
the different possible needs.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><strong>Data
acquisition</strong></p>
<p style="margin-bottom: 0cm; line-height: 100%">The first phase
consists, of course, in creating the device for data acquisition.</p>
<p style="margin-bottom: 0cm; line-height: 100%">In this case, we
will use the following components:</p>
<ul>
	<li><p style="margin-bottom: 0cm; line-height: 100%">Raspberry Pi 4
	(given the characteristics of the project it is possible to use any
	of the models with a 40-pin connector);</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">BME280 Olimex
	sensor (here too, any sensor with Bosch BME280 chip can be used,
	subject to some changes compared to the configuration adopted in
	this laboratory, which may be necessary to correctly address the
	sensor on the I2C bus).</p>
</ul>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">The BME280 Olimex
sensor can be used with I2C or SPI buses; in this case, the
communication on the I2C bus was used.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">With reference to
the I2C standard, the rasperry operates as a master while the BME280
sensor is a slave.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">The wiring of the
sensor to the raspberry takes place as follows:</p>
<ol>
	<li><p style="margin-bottom: 0cm; line-height: 100%">The VCC pin of
	the sensor must be connected to pin 1 of the 40-pin connector of the
	rasperry, which provides a 3.3V power supply.</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">The GND pin of
	the sensor must be connected to pin 6 of the 40 pin connector of the
	rasperry to have a common reference of the voltages.</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">The SCL pin of
	the sensor must be connected to pin 5 of the 40-pin connector (BCM
	GPIO 3) of the rasperry, which provides the clock reference of the
	I2C bus.</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">The SDA pin of
	the sensor must be connected to pin 3 of the 40-pin connector (BCM
	GPIO 2) of the raspberry so that the two devices can exchange data.</p>
</ol>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">The following figure
shows the prototype with the connections presented.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="./images/html_a0d14455797bf288.jpg" name="Image1" alt="No alt text provided for this image" align="bottom" width="556" height="382" border="0"/>
</p>
<p style="margin-bottom: 0cm; line-height: 100%">In order for the
raspberry to communicate with the sensor, make sure that the I2C
interface is enabled.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">To do this it is
necessary:</p>
<ol>
	<li><p style="margin-bottom: 0cm; line-height: 100%">From the
	command line type &quot;sudo raspi-config&quot;</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">Select option 5
	&quot;Interfacing Options&quot;</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">Select option
	P5 &quot;I2C&quot;</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">Select “Yes”
	when asked to activate the I2C bus</p>
	<li><p style="margin-bottom: 0cm; line-height: 100%">Reboot the
	raspberry</p>
</ol>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">Now you need to have
the software needed to call up the BME280 in order to configure and
control the reading operations.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">These labs use the
source code of the chip manufacturer (Bosch), which can be found on
GitHub at https://github.com/BoschSensortec/BME280_driver.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">As you can see,
there are basically three files in &quot;C&quot; language (bme280.c,
bme280.h, bme280_defs.h) which, compiled into a library, make the
communication operations with the sensor available to the software
programs that call it.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">To compile the
software, a project was created using the “Geany” IDE, available
in the RaspiOS operating system, in which the three files were
loaded.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">Furthermore, some
other files have been added to the project, the files
&quot;linux_userspace.h&quot; and &quot;linux_userspace.c&quot;,
derived from the example available in the Bosch &quot;examples&quot;
folder, which contain higher level structures and functions using the
basic functions in the &quot;bme280.c&quot; file, and the files
&quot;bme280func.h&quot; and &quot;bme280func.c&quot;, with the
functions that will be used for reading the environmental parameters
from the applications created in this laboratory.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">In particular, the
&quot;bme280func.c&quot; file contains 3 functions:</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">get_one_sample: it
is a function able to open a communication channel with the sensor,
perform a sampling of the environmental quantities and close the
communication with the sensor.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">get_sensor_data_forced_mode:
is a function called by “get_one_sample” that configures the
operating mode of the sensor, based on its specifications
(retrievable at the link
https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf),
and read it when a communication channel is available.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">print_sample: is a
function that calls the “print_sensor_data” function in the
“linux_userspace.c” file to print the acquired values.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">The complete library
code is available at&nbsp;https://github.com/old-malloc/libbme280&nbsp;.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">Once the code has
been compiled through the Makefile of the project, the “libbme280.so”
shared library is generated.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">To verify the
functioning of the library, a simple test program has been created
which reads the environmental quantities every 5 seconds and prints
them on the screen.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">The complete program
code is available
at&nbsp;https://github.com/old-malloc/libbme280/tree/main/bme280test&nbsp;.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">To compile the
program correctly, the header files &quot;bme280_defs.h&quot;,
&quot;bme280.h&quot; and &quot;linux_userspace.h&quot; and the shared
library must be in the same folder as the &quot;main.c&quot; file.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%">By launching the
“bme280test” executable file, the raspberry starts reading the
values measured by the sensor and prints them in the command window
(figure below).</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
<p style="margin-bottom: 0cm; line-height: 100%"><img src="./images/html_5e74c4c3c3811b4e.png" name="Image2" alt="No alt text provided for this image" align="bottom" width="592" height="356" border="0"/>
</p>
<p style="margin-bottom: 0cm; line-height: 100%">In the next article,
the shared library will be used to create a graphical web monitor in
python language for displaying measurements.</p>
<p style="margin-bottom: 0cm; line-height: 100%"><br/>

</p>
