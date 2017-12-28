<div>

<div id="greeting">
    <?php
        print("User: " . $cash[0]["username"]);
        print("  -    Balance: $" . sprintf("%.2f",$cash[0]["cash"]));
    ?>
    
</div>

<table id="transactions">
    <?php

        print("<tr>");
            print("<th>Symbol</th>");
            print("<th>Status</th>");
            print("<th>Shares</th>");
            print("<th>Price</th>");
            print("<th>Date</th>");
        print("</tr>");
        
        foreach ($positions as $position){
            print("<tr>");
            print("<td>" . $position["symbol"] . " </td>");
            print("<td>" . $position["status"] . " </td>");
            print("<td>" . $position["shares"] . " </td>");
            print("<td>" . "$" . $position["price"] . " </td>");
            print("<td>" . $position["timestamp"] . " </td>");
            print("</tr>");
        }

    ?>
</table>

</div>
