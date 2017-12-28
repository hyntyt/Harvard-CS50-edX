<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO #2/7: search database for places matching $_GET["geo"], store in $places
    $searchkey = $_GET["geo"];
    
    //Ran this query below in pset8/places table to create FULLTEXT indexes joinlty: 
    //CREATE FULLTEXT INDEX locations ON places(postal_code, place_name, admin_name1, admin_name2)
    
    $places = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1, admin_name2) AGAINST (?)", $searchkey);
    //32431, Atlanta, Georgia, Cobb County
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>