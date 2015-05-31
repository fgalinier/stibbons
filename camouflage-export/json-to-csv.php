#!/usr/bin/php
<?php
	if(count($argv) < 2) {
		echo "Usage: \n\tjson-to-csv.php <filename>\n";
		exit();
	}
	
	$json = json_decode(file_get_contents('./'.$argv[1]), true);
	
	echo 'id,breed,color,angle,position,properties,parent',"\n";
	foreach($json["Turtles"] as $turtle) {
		foreach($turtle as $id => $properties) {
			echo $id, ',';
			foreach($properties as $p) {
				if(is_array($p)) {
					foreach($p as $key => $val) {
						echo $key,':',$val;
						if($val !== end($p)) echo ';';
					}
				}
				else echo $p;
				if($p !== end($properties))	echo ',';
			}
			echo "\n";
		}
	}
