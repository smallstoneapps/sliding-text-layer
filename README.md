# Sliding Text Layer

A Layer for your Pebble apps that lets you vertically scroll a line of text.

![](https://images.unsplash.com/photo-1461724947009-3c626ff3d2bc?dpr=1&auto=format&fit=crop&w=767&h=511&q=80&cs=tinysrgb&crop=)

*As of January 2017, this library is officially abandoned.*

---

![](screenshot.gif)

## Installation

*You must be using Pebble SDK 3.12 or newer to use this library.*

To install the package to your app, use the pebble tool:

```
pebble package install @smallstoneapps/sliding-text-layer
```

## Usage

2. Include the header file in your code.

    ```
    #include <@smallstoneapps/sliding-text-layer/sliding-text-layer.h>
    ```
3. Create a new SlidingTextLayer.

    ```
    SlidingTextLayer* stl = sliding_text_layer_create(GRect(0, 60, 144, 24));
    ```
4. Set the initial text for the layer.

    ```
    sliding_text_layer_set_text(stl, "Line 1");
    ```
5. When you want to animate to the next line of text.

    ```
    sliding_text_layer_set_next_text(stl, "Line 2");
    sliding_text_layer_animate_down(stl);
    ```
