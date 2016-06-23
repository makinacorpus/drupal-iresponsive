<img<?php print $attributes; ?>
  srcset="<?php foreach ($derivatives as $derivative): ?><?php echo $derivative['href']; ?> <?php echo $derivative['width']; ?>w,<?php endforeach; ?>"
  sizes="<?php echo $viewport; ?>vw"
  <?php if ($default): ?>
  src="<?php echo $default['href']; ?>"
  <?php if ($image_alt): ?>alt="<?php echo $image_alt; ?>"<?php endif; ?>
  <?php if ($image_title): ?>title="<?php echo $image_title; ?>"<?php endif; ?>
  <?php endif; ?>
  />