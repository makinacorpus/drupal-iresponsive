<?php
/**
 * @file
 * Field module related hooks.
 */

/**
 * Implements hook_field_widget_info().
 */
function iresponsive_field_formatter_info() {
  return [
    'iresponsive' => [
      'label'       => t("Responsive image"),
      'field types' => ['image'],
      'settings'    => [
        'html_tag'      => 'img',
        'modifier'      => 'w',
        'default_size'  => null,
        'include_full'  => true,
        'viewport'      => 100,
      ],
    ],
  ];
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function iresponsive_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {

  $display  = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element  = [];

  switch ($display['type']) {

    case 'iresponsive':
      $element['html_tag'] = [
        '#title'          => t("HTML tag"),
        '#type'           => 'radios',
        '#options'        => [
          'img'           => t('&lt;img&gt; suitable for most cases'),
          'picture'       => t("&lt;picture&gt; you should use this for fullscreen display"),
        ],
        '#description'    => t("HTML &lt;picture&gt; element does not handle the viewport relative size attribute, it's not suitable for thumbnail display"),
        '#default_value'  => $settings['html_tag'],
        '#required'       => true,
      ];
      $element['modifier'] = [
        '#title'          => t("Display mode"),
        '#type'           => 'select',
        '#options'        => [
          'w'             => t("Keep image original ratio"),
          's'             => t("Square image"),
        ],
        '#default_value'  => $settings['modifier'],
        '#required'       => true,
      ];
      $element['default_size'] = [
        '#title'          => t("Graceful downgrade size"),
        '#type'           => 'select',
        '#options'        => drupal_map_assoc(iresponsive_image_size_list()),
        '#empty_option'   => t("Smallest one (default)"),
        '#default_value'  => $settings['default_size'],
        '#required'       => false,
      ];
      $element['include_full'] = [
        '#title'          => t("Include original image in variants"),
        '#type'           => 'checkbox',
        '#default_value'  => $settings['include_full'],
      ];
      $element['viewport'] = [
        '#title'          => t("Viewport relative size (in percent)"),
        '#type'           => 'select',
        '#options'        => drupal_map_assoc([10, 20, 30, 40, 50, 60, 70, 80, 90, 100]),
        '#default_value'  => $settings['viewport'],
        '#required'       => true,
      ];
      break;
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function iresponsive_field_formatter_settings_summary($field, $instance, $view_mode) {

  $display  = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = [];

  switch ($display['type']) {

    case 'iresponsive':
      $summary[] = $settings['html_tag'];
      $summary[] = $settings['viewport'] . 'vh';
      if ($settings['include_full']) {
        $summary[] = t("with original");
      }
      break;
  }

  return implode(', ', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function iresponsive_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {

  $element  = [];
  $settings = $display['settings'];

  switch ($display['type']) {

    case 'iresponsive':
      foreach ($items as $delta => $item) {
        $element[$delta] = [
          '#theme'        => 'iresponsive_' . $settings['html_tag'],
          '#image_uri'    => $item['uri'],
          '#image_width'  => $item['width'],
          '#image_height' => $item['height'],
          '#image_alt'    => $item['alt'],
          '#image_title'  => $item['title'],
          '#modifier'     => $settings['modifier'],
          '#default_size' => $settings['default_size'],
          '#include_full' => $settings['include_full'],
          '#viewport'     => $settings['viewport'],
        ];
      }
      break;
  }

  return $element;
}
