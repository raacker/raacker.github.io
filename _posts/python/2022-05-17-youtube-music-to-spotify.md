---
title: "Export playlists from Youtube Music to Spotify or the other way"
last_modified_at: 2022-05-17T22:21:00-08:00
categories:
    - Toy
tags:
    - [python]
excerpt: "If you are a my-own-playlist manager like me, you may find useful from my export, import playlist project"
---

TBH, it is not that intesting idea for most of people. 

But if you are a playlist DJ, like me, who likes to collect all the music data in manners and create a ***carefully curated playlist*** depends on moods, time, categories or any purpose, you would like to see these scripts.

Okay, my passion to music is quite high and I think I know quite a bit of songs to recommend to people! Or if my friends come over to my home, I am very ready to play an awesome playlist for my friends to hangout 😛

But my most painful problem over the years was that I cannot stick to a solid platform I want to use. 

Genie, it is a Korean platform which doesn't have lots of non-korean songs (it even didn't have "Kings of Convenience" songs back then! Can you believe this? Jesus). Worst UI, lacks, crashes... throw away.

Melon, another Korean platform but pretty decent. But still, I was not a big fan of Korean songs. Mostly biased to Heavy Metals, Pops, all other songs written in English or Rammstein.

Google Music, the anscestor of Youtube Music. I used this for 3 or 4 years. I had all of my playlist in Google Music at the end and when Google has launched Youtube Red, I had to manually move all of them over to the new platform. I think I lost some of songs I liked 😞

Youtube Music, enjoyed quite a bit. It is not a best platform to listen and maintain your playlist but it has a powerful ability which is you can watch or play youtube video as well. Because some of songs are not listed as a song due to any legal or country lock related reasons. But some of videos are alive or sometimes you find a best live version that beats studio version but only can find in youtube video. 

At last, I made a favored nest on Spotify. I'm enjoying it so much so far and have been having not many issues. Pretty satisfied.

But you would already notice that this kind of platform switches are pretty common if you are into listening songs to be honest. Well time goes by, the dominant changes... but what about our playlist? mostly they are very coupled to your own platform you are using. Once you are locked in to your platform, it's pretty hard to move around and even you would have a chance to lose them by any reasons.

That's why I started my Notion Table database for my songs with my-own-categorization project. It already has been a couple years now and I've been very happy with it. I will not cover how I am maintaining my database in this article but I would love to share it someday.

<br/>
Sorry, long story. Let's get to the point.

I wrote some scripts using ytmusicapi and spotipy libraries to import & export playlist in CSV format with just a song name and an artist name. Actually that's pretty much all you really need to import & export into other platforms.

[playlist_trader](https://github.com/raacker/playlist_trader)

The scripts are very straightforward, read the README.md to setup and just run the scripts with your playlist ids.

The major problem you will encounter is that some of songs do not have the same name in other platforms. Sometimes they don't have Korean translation, Spanish translation, cannot be searched, etc. Thus, when the script fails to add, it will show you the list of failed songs.

I have a plan to make a standalone program that any other people can use based on these scripts to easy import & export playlists in between platforms so bear with me! 