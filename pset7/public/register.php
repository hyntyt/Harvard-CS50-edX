<?php

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("register_form.php", ["title" => "Register"]);
    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO #1/7
        
        // Ensure that the username field is is filled, and not empty
        if(empty($_POST["username"])){
            apologize("Invalid username.");
        }
        
        // Ensure username and password fields are filled, and not empty
        if(empty($_POST["username"]) || empty($_POST["password"])){
            apologize("Invalid password.");
        }
        
        // Ensure password field is the same as the password confirmation field
        if($_POST["password"] != $_POST["confirm"]){
            apologize("Password was not confirmed.");
        }
        else{
            
            // Ensure username is available
            $reslt = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
            if($reslt == true){
                apologize("User already exists.");
            }else{
                
                // Suggested code from walkthrough at http://cdn.cs50.net/2016/x/psets/7/pset7/pset7.html
                // Insert valid new user to the database, hashing their inputed password
                $reslt = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                
                // Log new user in with their credentials
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                redirect("index.php");
            }
        }
    }
?>