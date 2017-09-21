//
//  twitclient.hpp
//  proj
//
//  Created by Andrey Losev on 7/25/17.
//  Copyright © 2017 Andrey Losev. All rights reserved.
//

#ifndef twitclient_hpp
#define twitclient_hpp
#include <string>
struct OauthTwitPass
{
    std::string key;
    std::string secret;
    std::string consumerKey;
    std::string consumerSecret;
};
void tweetauth(OauthTwitPass& pass);
void tweet(const std::string& text, OauthTwitPass& pass);
#endif /* twitclient_hpp */
