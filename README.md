# Responsive image formatter for Drupal

This module brings theme functions and a field formatter to display responsive
images. It supports two different HTML tags:

 *  **&lt;IMG&gt;** tag using *srcsrc* attribute;
 *  **&lt;PICTURE&gt;** tag using *&lt;SOURCE&gt;* elements.

The &lt;IMG&gt; tag supports the *sizes* attribute allowing to set a relative viewport
sizes for images at the field display configuration level, allowing the browser
to proceed with better image selection for download.

This modules won't allow you to provide your own image styles, it only provides
two different modes:

 *  Image keeps the original image ratio;
 *  Square image.

Future plans is to support more complex image styles (maybe by merging this
module own styles using a user provided one).

This ships the [Picturefill 2.0](https://scottjehl.github.io/picturefill/)
polyfill to ensure graceful downgrade for old browsers.

## Installation

Just download and enable the module.

## Confguration

You may want to override available sizes for images, default is:

```[285, 570, 855, 1140, 1440]```

In order to override it, just add in your settings.php file:

```php
$conf['iresponsive_image_size_list'] = [200, 300, 500, 1400, ...];
```

## Usage

### For image fields

Select *Responsive image* as display formatter, quite straightforward ?

### Displaying manually an image

Use one of ```ireponsive_img``` or ```iresponsive_picture``` theme hooks and
proceed this way with render arrays:

```php
// Considering that $file is loaded file_managed.
$build['my_image'] = [
  '#theme'        => 'iresponsive_picture',
  '#image_uri'    => $file->uri,
  '#image_width'  => $file->width,
  '#image_height' => $file->height,
  '#image_alt'    => t("Some alternative text"),
  '#image_title'  => t("Some HTML title tag"),
  // Note that 'w' is the default, and keeps ratio while 's' is for square.
  '#modifier'     => 'w',
  // Default size must exist in iresponsive_image_size_list() function defaults
  // the 'iresponsive_image_size_list' variable if you overrided it.
  '#default_size' => $settings['default_size'],
  // If you set to true, this will include the original image, but without
  // any transformation (no square, etc...) in the image sources.
  '#include_full' => false,
  // Targetted image size in viewport percent (aka 'vh' unit in CSS).
  '#viewport'     => 50,
];
```

Or if you write Drupal 6 old school code (but you should never do this):

```php
// Considering that $file is loaded file_managed.
theme(''iresponsive_picture', [
  'image_uri'    => $file->uri,
  'image_width'  => $file->width,
  'image_height' => $file->height,
  'image_alt'    => t("Some alternative text"),
  'image_title'  => t("Some HTML title tag"),
  // Note that 'w' is the default, and keeps ratio while 's' is for square.
  'modifier'     => 'w',
  // Default size must exist in iresponsive_image_size_list() function defaults
  // the 'iresponsive_image_size_list' variable if you overrided it.
  'default_size' => $settings['default_size'],
  // If you set to true, this will include the original image, but without
  // any transformation (no square, etc...) in the image sources.
  'include_full' => false,
  // Targetted image size in viewport percent (aka 'vh' unit in CSS).
  'viewport'     => 50,
]);
```
