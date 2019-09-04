/*
>- Author: Max Wong
>- Date: Apr 23, 2019
>- Updated: April 23, 2019
>- Purpose: To make some prototype/concept art
>-
>- [version 2.0.0.5]
*/

#include <iostream>
#include <conio.h>
#include <math.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main()
{
    //Defining the variables
    string randInput = "";
    string userID = "";
    char ch;

    //Fake program startup
    cout << endl << endl;
    cout << ">- Rebooting..." << endl;
    cout << "   [Press enter to continue]" << endl << endl;
    getch();

    for( int i = 0; i < 20; i++)
    {
        cout << endl;
        cout << ">-                Starting-up. Stand by." << endl;
        cout << ">- " << endl;
        cout << ">- " << endl;
        cout << ">-                   Loading..." << endl;
        cout << "              [";

        for(int j = i; j > 0; j--)
        {
            cout << "#";
        }
        for(int k = 20 - i; k > 0; k--)
        {
            cout << " ";
        }
        cout << "]" << endl;
        Sleep( 5 );

        system("CLS");
    }

    cout << endl << ">-" << endl;
    cout << ">- System at 100%" << endl;
    cout <<     "[Press any key to begin connecting]" << endl;
    getch();

    //Fake server connection animation
    system("color A");
    for(int i = 0; i < 100; i+= 10 )
    {
        cout << ">- -UNSC User Management System-" << endl;
        cout << "================================" << endl;
        cout << "________________________________" << endl;
        cout << "UNSC TacOS  v.337" <<  endl;
        cout << "(S) 2294 FLEETCOM" << endl;
        cout << "=======================" <<  endl;
        cout << "|  User Log:" << endl;
        cout << "|  >> Administrator (UNSC ID 8384-C)" << endl;
        cout << "|  >>> " << "unknown.GUEST_userGroup" << endl;

        cout << endl << endl << "connecting to [UNSC REACH] servers" << endl;
        cout << "connecting";
        if( (i % 3) == 1 )
        {
            cout << "." << endl;
        }
        else if ( (i % 3) == 2 )
        {
            cout << ".." << endl;
        }
        else if ( (i % 3) == 0 )
        {
            cout << "..." << endl;
        }

        cout << "Status: [" << i << "%]" << endl;
        Sleep ( 1 );
        system("CLS");
    }

    //When server is connected
    cout << ">- -UNSC User Management System-" << endl;
    cout << "================================" << endl;
    cout << "________________________________" << endl;
    cout << "UNSC TacOS  v.337" <<  endl;
    cout << "(S) 2294 FLEETCOM" << endl;
    cout << "=======================" <<  endl;
    cout << "|  User Log:" << endl;
    cout << "|  >> Administrator (UNSC ID 8384-C)" << endl;
    cout << "|  >>> " << "unknown.GUEST_userGroup" << endl;
    cout << endl << endl;

    cout << ">- connecting to [UNSC REACH] servers" << endl;
    cout << ">- connection established" << endl;
    cout << ">- Status: [100%]" << endl;

    cout << endl << ">- " << endl;
    cout << ">- Authenticating" << endl;
    cout << endl << ">- " << endl;
    cout << ">- UNSC.ID detected" << endl;
    cout << ">- NAVCOM.ID undetected" << endl;
    cout << ">- FLEETCOM.ID undetected" << endl;
    cout << ">- ONI.ID detected" << endl;
    cout << endl;

    cout << "________________________________" << endl;
    cout << "================================" << endl;
    cout << "[AUTHENTICATION COMPLETE]" << endl;
    cout << ">- Please enter your pin and ID" << endl << endl;
    getch();

    cout << ">- ID: ";
    cin >> userID;
    cout << ">- PIN: ";

    //Fake username and password system. Converts all letters into *'s
    ch = _getch();
    while(ch != 13)
    {
        randInput.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl;
    if(randInput == "cheats.activate")
    {
        cout << ">- \Admin hacks activated." << endl;
        cout << ">- Welcome " << userID << endl;
    }
    else
    {
        cout << ">- \Acess Granted." << endl;
        cout << ">- Welcome " << userID << endl;
    }
    cout << endl << "    [Press any key to continue]" << endl;

    getch();

    //Load main menu/screen
    cout << endl;
    system("CLS");
    cout << "                                                                     ..oydddddhsoss`" << endl;
    cout << "                                                               :+oo/+mmmmmmmmmmmmmmy..oo-" << endl;
    cout << "                                       `..                  :smNNNNNNNNNNNNNNNNNNNNNmd+`" << endl;
    cout << "                             `/+o+/oo/--oss.:+/-`````    `:yhdhdmNNNNNNNNNNNNNNNNNNNN/                                             .-:::/`          ```-:--/so////-            `---." << endl;
    cout << "                            /syyhhsyyym+-:s+.s/:yh/yho+/.       `-dNNNNNNNNNNNNNNNNhs-                                         `/sy/.....:+.. :.:+ohmmmmmmmmmmmmmmyo++:/ooo`   `-hdo::." << endl;
    cout << "     .:osydhsosoo+///.///o+/shy/ymmmmmmdo/.o.+y:ysymdyshmdhy/`    -hhNNNNNNNNNNNNho/                       .:+osyyso+:.``  ..  ./so.-/:-ommos+ymdsmmmmmmmmmmmmmmmmmmmmmmmmmhhdddmmmmmmmdhhhho//++/:o///-" << endl;
    cout << "    -osymmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdhhhdhhmmmhhho`.osdmmmyy/`  +NMMMMMmhhs--.`  ./::/:               :ymmmmyhmmmmmysoyoyhhdmmmmmmmmmmmdsdmdmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmms" << endl;
    cout << "    `ohymmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmh+:./:/-.+oossyo-`    :hNMMy.          -/o:.           .+sdmNNhooymNNmdmdmdmNmNNNNNNNNNNNNNNmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNddmmNNNNmdys-" << endl;
    cout << "    .-+oyhmmy+/..-:+shmmmmmmmmmmmmmmmmmmmmmmmy.       -mmmdy:os.      .-/`                    `.:`   .dmyNNNy``+ssyNhmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmysssooys::ods::::.`" << endl;
    cout << "    ` -:++:/-        `/ydmmmmmmmmmmmmmmmmmmmmmddyo+/.`/hmmmmmmmmo/`                          -ohdy`   `yssso:.hmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNd+-       `hmmh." << endl;
    cout << "-. `: ``               .+:dmmmmmmmmmmmmmmmmmmmmmmmmmd+hmmmmmmmmmmdy.                        `hy:dmd+:sdmNmmmmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmddy:      yy-`" << endl;
    cout << "                          ./yhNNNNNNNNNNNNNNNNNdy+ommmmNNNNmhy++-/ys:                        `  :sdmNNNNNNNNNNNNNNNNNNNNNNNNNNNddNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNsso      ." << endl;
    cout << "                            /mNNNNNNNNNNNNNNNNNmms+d:hhdNNNdydho+````                        `.../NNNNNdmdymNNNNNNm+-y+/hNNNd.-oomNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNms-`o/." << endl;
    cout << "                            /NNNNNNNNNNNNNNNNNNNNydNhhdmNhy.`.``                             smmmmmh+../-sssodNNdmo:/so//oNNNy/.yNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNdNmNNy:-.  y+:." << endl;
    cout << "                            `smNNNNNNNNNNNNNNNNNNNNNNNNm+`                                   sdNdd+-:--+.`//.`yd-odmNNmNNNNNNm/.:NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNs//:hm-   .:m." << endl;
    cout << "                              :sdNNNNNNNNNNNNNNNNNNNNmh/                                     .+hyhddmmmmy```  `.  `...oNNNNNNNNmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNo` :y/syss+-" << endl;
    cout << "                                -dymNNNNNNNNNmdmhyhmm-`                                     `hmmmmmmmmmmmdho/+hhysooooNNNNNNNNhNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN-   -/.`" << endl;
    cout << "                                 .yyymNNNNNm/...` `-h/                                    .ohmmmmmmmmmmmmmmmmmmmmmmmNm+mNNNNNNo/ydhNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNh." << endl;
    cout << "                                  `:+/yNNNNh       `::-                                  -dmmmmmmmmmmmmmmmmmmmmmmmmmmms:mMMMMMNh+hhy///-+hMNMMMMMMMNNmNMMMMMMMMNMNNmy-+`" << endl;
    cout << "                                       smNNm:`.+h+ `..-/`.:- `                           oNNNNNNNNNNNNNNNNNNNNNNNNNNNNNo:hMMMMMMMMNy`    `+hMMMMMNh:-./mMMMMMMy/d--.  .`" << endl;
    cout << "                                        .:yhdsdmN:-.  .. .:- .                           oNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNy.yMMMNmdy:        /MMMNy:`    /dhMMMMmo:    `s/" << endl;
    cout << "                                            ` -+oyNy     .`.                             dNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNdshyo/-`           sMMd       ``-NyNMMN:    `o+-." << endl;
    cout << "                                                  oy-::-ymydyshy/`                       .+mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmsyhd-             oNo.        `s`-yy/`     .o+/" << endl;
    cout << "                                                   `-.:NNNNNNNNNmd+/:`                     .odmdddho/hmdNNNNNNNNNNNNNNNNNNNNNm/              `-:-       ../h-     `-+` -+/" << endl;
    cout << "                                                     `/NNNNNNNNNNNNNNh-                      ..```   `-.mNNNNNNNNNNNNNNNNNNdy-                          ./osh.  -ohmm.``` .`" << endl;
    cout << "                                                     yNNNNNNNNNNNNNNNdh++-```                          :mNNNNNNNNNNNhsNNNm+`                              -dd+` hNNNo-so. :`:+///-``" << endl;
    cout << "                                                    `dNNNNNNNNNNNNNNNNmNNNmdh+-                         :dNNNNNNNNNNNNNNh.                                 .om:``::/`-:s     /oydNdh/`" << endl;
    cout << "                                                     -dNNNNNNNNNNNNNNNNNNNNNNNm`                         -NNNNNNNNNNNNNNd`                                   `::-+/  `  -:      :hmsoy:" << endl;
    cout << "                                                      .dNNNNNNNNNNNNNNNNNNNNNh-                          `dNNNNNNNNNNNNNN+   `.                                      `` -. `:/:.  s` .:" << endl;
    cout << "                                                       .ymNNNNNNNNNNNNNNNNNNh                            hMMMMMMMMMMMMMNN: .:hm                                        `-hshmmm+.`yh:                  `" << endl;
    cout << "                                                         `:NMMMMMMMMMMMMMMMN+                            +NMMMMMMMMMMMd+-  hNN+                                    ``.-dmNNNNNNNmhmNm-`        `      `-" << endl;
    cout << "                                                           NMMMMMMMMMMMNNmdo                              +MMMMMMMMMMMo    dMh                                    /hmmNNNNNNNNNNNNNNNNh-       -." << endl;
    cout << "                                                          .MMMMMMMMMMMMs-`                                 mMMMMMMMMMo.    /o.                                    oNNNNNNNNNNNNNNNNNNNNN:" << endl;
    cout << "                                                          sMMMMMMMMMMNh.                                   -dMMMMMMNo`                                            .dNNNNNNNNNNNNNNNNNNNNs" << endl;
    cout << "                                                         `mMMMMMMNNNm:                                      -NNNNds.                                               +NNNNy//--+dhNMMMMMMN:" << endl;
    cout << "                                                         sMMMMMMMNs-`                                        .`                                                    -/:``      . -hNMMNN-            /-`" << endl;
    cout << "                                                         mMMMMms/:                                                                                                               `-://`            ./d:" << endl;
    cout << "                                                        .NMMMm:                                                                                                                     ++          `/yh:" << endl;
    cout << "                                                        hMMMN/                                                                                                                                  -+:" << endl;
    cout << "                                                        oMMm/" << endl;
    cout << "                                                         +yNs-" << endl;

    cout << endl;
    cout << "      __          ______" << endl;
    cout << "     /  \\       |  __  |" << endl;
    cout << "    / /\\ \\      | |__| |" << endl;
    cout << "   / /__\\ \\     | |" << endl;
    cout << "  /  ____  \\    | |" << endl;
    cout << " / /      \\ \\   | |" << endl;
    cout << "/_/        \\_\\  |_|" << endl;


}
