<?php

function theme_cachebustimage($variables) {
  $attributes = $variables['attributes'];
  $path = drupal_parse_url($variables['path']);
  $token_query = $path['query'];
  $internal_path = str_replace($GLOBALS['base_url'] . '/', '', $path['path']);

  if (is_file($internal_path)) {
    $cachebust = filemtime($internal_path);
  }
  else {
    $cachebust = time();
  }
  $token_query += array('time' => $cachebust);
  $file_url = file_create_url($path['path']);

  $attributes['src'] =  $file_url . (strpos($file_url, '?') !== FALSE ? '&' : '?') . drupal_http_build_query($token_query) ;

  foreach (array('width', 'height', 'alt', 'title') as $key) {

    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<img' . drupal_attributes($attributes) . ' />';
}
