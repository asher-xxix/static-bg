# static-bg       [no longer maintained]
A Pebble static background watchface.
------------------
This was just a tiny project that created a simple static watchface for the Pebble Time smartwatch. Nothing to do with nuclear fusion, really.


![](pebble_screenshot_2015-09-19_19-54-52.png)


To install this on your pebble make sure you have the dev connection enabled on your phone and the pebble sdk is installed on your computer. THe sdk can be gotten with

`brew install pebble/pebble-sdk/pebble-sdk
`

Then use

`pebble build && pebble install --phone <your phone ip here>`

inside the root folder of this watchface and it will be installed to your pebble!


### Things to Add
- current date
- battery indicator (if possible)
- temperature
