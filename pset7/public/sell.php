<?php 
    
    // configuration
    require("../includes/config.php");
    
    if($_SERVER["REQUEST_METHOD"] == "POST"){ //POST
        
        $input = $_POST["symbol"]; 
        $idp = $_SESSION["id"];
        
        if($input != false){
            
            $stockheld = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? and symbol = ?", $idp, $input);
            
            if(count($stockheld) >= 1){
               
                // Determine the number of shares held
                $sharesheld = $stockheld[0]["shares"]; //works
               
                $stock = lookup($_POST["symbol"]);
                
                // Determine the current price of the stock to sell
                $sellprice = $stock["price"];
                $stocksymbol = $stock["symbol"];
                
                // Determine the total revenue associated with the sale, by multiplying the price by the number of shares
                $revenue = $sellprice * $sharesheld; 
                
                // Determine the old balance and add the total revenue to it, to determine the new balance
                $balancequery = CS50::query("SELECT cash FROM users WHERE id=$idp");
                $balance = $balancequery[0]["cash"];
                $newbalance = $balance + $revenue;
                
                // Update database accordingly
                CS50::query("DELETE FROM portfolios WHERE user_id = $idp AND symbol = '$stocksymbol'"); //delete stock from portfolio (works)
                CS50::query("UPDATE users SET cash = $newbalance WHERE id = $idp"); //update the cash position (works)
               
               // Log transaction accordingly 
                CS50::query("INSERT INTO transactions (id, symbol, status, shares, price, timestamp) VALUES ($idp, '$stocksymbol', 'SELL', $sharesheld, $sellprice, NOW())");
                 
            }
            else{
                apologize("Stock is valid, but you do not own any shares.");
            }
       
        }
        else{
            apologize("Stock that you attmped to sell does not exist.");
        }
       render("sell_summary.php", ["title" => "Stock Sale Summary", "stock" => $stock, "revenue" => $revenue, "newbalance" => $newbalance]); //works not rounded
       //redirect("/"); //for testing, would prefer redner line above for sell_summary.php page
    }
    else{ //GET
        $idg = $_SESSION["id"];
        $ownedstocks = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $idg);
        render("sell_form.php", ["rows" => $ownedstocks, "title" => "Sell Stock Holdings"]); 
    }
    
?>