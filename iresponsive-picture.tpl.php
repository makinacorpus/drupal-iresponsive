<picture>
  <?php foreach ($derivatives as $derivative): ?>
  <source srcset="<?php echo $derivative['href']; ?>" media="(max-width: <?php echo $derivative['width']; ?>px)"/>
  <?php endforeach; ?>
  <img
    srcset="<?php echo $default['href']; ?>"
    <?php if ($image_alt): ?>alt="<?php echo $image_alt; ?>"<?php endif; ?>
  />
</picture>