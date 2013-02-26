<?php

function theme_cachebustimage($variables) {
  $attributes = $variables['attributes'];
  $internal_path = str_replace($GLOBALS['base_url'] . '/', '', $variables['path']);
  if (is_file($internal_path)) {
    $cachebust = filemtime($internal_path);
  }
  else {
    $cachebust = time();
  }
  
  $attributes['src'] = file_create_url($variables['path']);
  
  if (strstr($attributes['src'], '?')) {
    $attributes['src'] = $attributes['src'] . '&time=' . $cachebust;
  }
  else {
    $attributes['src'] = $attributes['src'] . '?time=' . $cachebust;
  }

  foreach (array('width', 'height', 'alt', 'title') as $key) {

    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<img' . drupal_attributes($attributes) . ' />';
}