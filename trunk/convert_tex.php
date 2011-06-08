#!/usr/bin/php
<?php
// convert_text.php for  in /home/jochau_g//Desktop/raytracer-42/3ds_models/ferrari/tex
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Wed Jun  8 12:14:33 2011 gael jochaud-du-plessix
// Last update Wed Jun  8 12:28:51 2011 gael jochaud-du-plessix
//

for ($i = 1; $i < $argc; $i++)
  {
    $filename = $argv[$i];
    $cmd = 'convert "' . $filename . '" "' . $filename . '.png"';
    echo $cmd . "\n";
    system($cmd);
    $cmd = 'mv "' . $filename . '.png" "' . $filename . '"';
    echo $cmd . "\n";
    system($cmd);
  }