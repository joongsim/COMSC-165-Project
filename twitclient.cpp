//
//  twitclient.cpp
//  proj
//
//  Created by Andrey Losev on 7/25/17.
//  Copyright © 2017 Andrey Losev. All rights reserved.
//
#include <iostream>
#include <string>
#include "twitcurl.h"
#include "twitclient.hpp"

void tweetauth(OauthTwitPass& pass)
{
    twitCurl twitterObj;
    twitterObj.setTwitterUsername( "165project" );
    twitterObj.setTwitterPassword( "thisis1password" );
    pass.consumerKey = "2i5UbKQWuTnAjb9pa6u8eI7Lb";
    pass.consumerSecret = "kTwAO62xdxyFvPu4wO2sfErKk3oP7CArZgTDxJp2ot0GS8R89m";
    twitterObj.getOAuth().setConsumerKey(pass.consumerKey);
    twitterObj.getOAuth().setConsumerSecret(pass.consumerSecret);
    std::string authUrl;
    twitterObj.oAuthRequestToken( authUrl );
    twitterObj.oAuthHandlePIN( authUrl );
    twitterObj.oAuthAccessToken();
    if( !twitterObj.accountVerifyCredGet() )
    {
        std::cout << "auth failed\n";
        return;
    }
    twitterObj.getOAuth().getOAuthTokenKey( pass.key );
    twitterObj.getOAuth().getOAuthTokenSecret( pass.secret );
}
void tweet(const std::string& text, OauthTwitPass& pass)
{
    twitCurl twitterObj;
    twitterObj.getOAuth().setConsumerKey(pass.consumerKey);
    twitterObj.getOAuth().setConsumerSecret(pass.consumerSecret);
    twitterObj.getOAuth().setOAuthTokenKey(pass.key);
    twitterObj.getOAuth().setOAuthTokenSecret(pass.secret);
    if( !twitterObj.statusUpdate(text))
    {
        std::cout << "post failed\n";
        return;
    }
    std::string apiResponse;
    twitterObj.getLastWebResponse(apiResponse);
    std::cout << apiResponse;
    std::cout << "\ngreat success\n";
}
