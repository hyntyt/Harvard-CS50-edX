<?php
    
    // configuration
    require("../includes/config.php"); 
    
    if($_SERVER["REQUEST_METHOD"] == "GET"){
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    else if($_SERVER["REQUEST_METHOD"] == "POST"){
        
        $stock = lookup($_POST["symbol"]);        
        
        if($stock != false){
            //$stock["price"] = CS50::decimal_format($stock["price"]);
            render("quote_display.php", ["title" => "Quote", "stock" => $stock]);
        }
        else{
            apologize("Invalid stock code.");        
        }
    }
    
?>