<picture<?php print $attributes; ?><?php if ($image_title): ?> title="<?php echo $image_title; ?>"<?php endif; ?>>
  <?php /* https://scottjehl.github.io/picturefill/#ie9 */ ?>
  <!--[if IE 9]><video style="display: none;"><![endif]-->
  <?php foreach ($derivatives as $derivative): ?>
  <source srcset="<?php echo $derivative['href']; ?>" media="(max-width: <?php echo $derivative['width']; ?>px)"/>
  <?php endforeach; ?>
  <!--[if IE 9]></video><![endif]-->
  <img
    style="width:100%"
    srcset="<?php echo $default['href']; ?>"
    <?php if ($image_alt): ?>alt="<?php echo $image_alt; ?>"<?php endif; ?>
  />
</picture>