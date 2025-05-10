#include<iostream>
using namespace std;
 int main(){
    int quant;
    int choice;

    // variable declaration
    int Qrooms=0, Qpasta=0, Qburger=0, Qnoodles=0, Qshake=0, Qchicken=0;                                // # of quantity
    int Srooms=0, Spasta=0, Sburger=0, Snoodles=0, Sshake=0, Schicken=0;                                // # of items sold
    int Total_rooms=0, Total_pasta=0, Total_burger=0, Total_noodles=0, Total_shake=0, Total_chicken=0;  // total price of each item 

    cout<<"\n\t Quantity of items we have";
    cout<<"\n Rooms avaliable: ";
    cin>>Qrooms;
    cout<<"\nQuantity of pasta: ";
    cin>>Qpasta;
    cout<<"\nQuantity of burger: ";
    cin>>Qburger;
    cout<<"\nQuantity of noodles: ";
    cin>>Qnoodles;
    cout<<"\nQuantity of shake: ";
    cin>>Qshake;
    cout<<"\nQuantity of chicken-roll: ";
    cin>>Qchicken;

    m:
    cout<<"\n\t\t\t Please select from the menu options ";
    cout<<"\n\n1) Rooms";
    cout<<"\n2) Pasta";
    cout<<"\n3) burger";
    cout<<"\n4) noodles";
    cout<<"\n5) shake";
    cout<<"\n6) chicken-roll";
    cout<<"\n7) Information regarding sales and collection ";
    cout<<"\n8) Exit";

    cout<<"\n\n Please Enter your choice ";
    cin>>choice;

    switch(choice){
        case 1:
            cout<<"\n\n Enter the number of rooms you want: ";
            cin>>quant;
            if(Qrooms-Srooms>=quant){
                Srooms=Srooms+quant;
                Total_rooms=Total_rooms+quant*1200;
                cout<<"\n\n\t\t"<<quant<<" room/rooms have been alloted to you";
            }
            else{
                cout<<"\n\tOnly"<<Qrooms-Srooms<<" Remaining in hotel ";
                break;
            }
        case 2:
            cout<<"\n\n Enter pasta quantity: ";
            cin>>quant;
            if(Qpasta-Spasta>=quant){
                Spasta=Spasta+quant;
                Total_pasta=Total_pasta+quant*250;
                cout<<"\n\n\t\t"<<quant<<" pasta is the order!";
            }
            else{
                cout<<"\n\tOnly"<<Qpasta-Spasta<<" Pasta Remaining in hotel ";
                break;
            }
        case 3:
            cout<<"\n\n Enter burger quantity: ";
            cin>>quant;
            if(Qburger-Sburger>=quant){
                Sburger=Sburger+quant;
                Total_burger=Total_burger+quant*120;
                cout<<"\n\n\t\t"<<quant<<" Burger is the order!";
            }
            else{
                cout<<"\n\tOnly"<<Qburger-Sburger<<" Burger Remaining in hotel ";
                break;
            } 
        case 4:
            cout<<"\n\n Enter noodles quantity: ";
            cin>>quant;
            if(Qnoodles-Snoodles>=quant){
                Snoodles=Snoodles+quant;
                Total_noodles=Total_noodles+quant*140;
                cout<<"\n\n\t\t"<<quant<<" Noodles is the order!";
            }
            else{
                cout<<"\n\tOnly"<<Qnoodles-Snoodles<<" Noodles Remaining in hotel ";
                break;
            } 
        case 5:
            cout<<"\n\n Enter shake quantity: ";
            cin>>quant;
            if(Qshake-Sshake>=quant){
                Sshake=Sshake+quant;
                Total_shake=Total_shake+quant*120;
                cout<<"\n\n\t\t"<<quant<<" Shake is the order!";
            }
            else{
                cout<<"\n\tOnly"<<Qshake-Sshake<<" Shake Remaining in hotel ";
                break;
            } 
        case 6:
            cout<<"\n\n Enter chicken-roll quantity: ";
            cin>>quant;
            if(Qchicken-Schicken>=quant){
                Schicken=Schicken+quant;
                Total_chicken=Total_chicken+quant*150;
                cout<<"\n\n\t\t"<<quant<<" Chicken-roll is the order!";
            }
            else{
                cout<<"\n\tOnly"<<Qchicken-Schicken<<" Chicken-roll Remaining in hotel ";
                break;
            } 
        case 7:
            cout<<"\n\tDetails of sales and collection ";
            cout<<"\n\n Number of rooms we had: "<<Qrooms;
            cout<<"\n\n Number of rooms we gave for rent "<<Srooms;
            cout<<"\n\n Remaining rooms: "<<Qrooms-Srooms;
            cout<<"\n\n Total rooms collection for the day: "<<Total_rooms;  
            
            cout<<"\n\n Number of pasta we had: "<<Qpasta;
            cout<<"\n\n Number of pasta we sold "<<Spasta;
            cout<<"\n\n Remaining pasta: "<<Qpasta-Spasta;
            cout<<"\n\n Total pasta collection for the day: "<<Total_pasta;

            cout<<"\n\n Number of burger we had: "<<Qburger;
            cout<<"\n\n Number of burger we sold "<<Sburger;
            cout<<"\n\n Remaining burger: "<<Qburger-Sburger;
            cout<<"\n\n Total burger collection for the day: "<<Total_burger;

            cout<<"\n\n Number of noodles  we had: "<<Qnoodles;
            cout<<"\n\n Number of noodles we sold "<<Snoodles;
            cout<<"\n\n Remainingnoodlesr: "<<Qnoodles-Snoodles;
            cout<<"\n\n Total noodles collection for the day: "<<Total_noodles;

            cout<<"\n\n Number of shake we had: "<<Qshake;
            cout<<"\n\n Number of shake we sold "<<Sshake;
            cout<<"\n\n Remaining shake: "<<Qshake-Sshake;
            cout<<"\n\n Total shake collection for the day: "<<Total_shake;

            cout<<"\n\n Number of chicken-roll we had: "<<Qchicken;
            cout<<"\n\n Number of chicken-roll we sold "<<Schicken;
            cout<<"\n\n Remaining chicken-roll: "<<Qpasta-Schicken;
            cout<<"\n\n Total chicken-roll collection for the day: "<<Total_chicken;

            cout<<"\n\n\n Total collection for the day: "<<Total_rooms+Total_pasta+Total_burger+Total_noodles+Total_shake+Total_chicken;
            break;

        case 8:
            exit(0);
            
            default:
                cout<<"\nPlease select the numbers mentioned above!";
    }
    goto m;
 }