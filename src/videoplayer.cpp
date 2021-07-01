#include "videoplayer.h"

#include <iostream>
#include <vector>
#include<algorithm>
#include<random>
#include<cctype>

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

bool comparator(std::string a, std::string b)
{
    return a < b;
}

void VideoPlayer::showAllVideos() {
  //Initialises vector of all videos in the library
  std::vector<Video> videos = mVideoLibrary.getVideos();
  //Initialises the number of videos available
  int vectorSize = mVideoLibrary.getVideos().size();
  std::cout << "Here's a list of all available videos:" << std::endl;

  //Creates a vector of video names
  std::vector<std::string> videoNames(vectorSize);
  for (size_t i = 0; i < vectorSize; i++)
  {
      videoNames[i] = videos[i].getTitle();
  }

  //Sorts the list of video names into lexicographical order
  std::sort(videoNames.begin(), videoNames.end(), comparator);

  //For loop in lexicographical order, displaying video information
  for (std::string videoName : videoNames) 
  {
      for (Video video : videos)
      {
          if (video.getTitle() == videoName) 
          {
              std::string hashtags = "";
              for (const std::string tag : video.getTags())
              {
                  hashtags += tag + " ";
              }

              if (hashtags.size() > 0) { hashtags.resize(hashtags.size() - 1); }
              std::cout << video.getTitle() << " (" << video.getVideoId() << ") [" << hashtags << "]" << std::endl;
          }
      }
  }
}

void VideoPlayer::playVideo(const std::string& videoId) {
    //Retrieves the user input Video
    const Video *videoPlay = mVideoLibrary.getVideo(videoId);
    
    //Checks if the user entered a valid Video ID
    if (videoPlay == nullptr) 
    {
        std::cout << "Cannot play video: Video does not exist" << std::endl;
    }
    else 
    {
        //If a video is currently playing, stop it
        if (!currentPlayingVideo.getTitle().empty()) 
        {
            std::cout << "Stopping video: " << currentPlayingVideo.getTitle() << std::endl;
        }
        //Play the desired video
        std::cout << "Playing video: " << videoPlay->getTitle() << std::endl;
        currentPlayingVideo = *videoPlay;
        paused = false;
    }
}

void VideoPlayer::stopVideo() 
{
    //Checks if there is a video currently playing, and stops it
    if (!currentPlayingVideo.getTitle().empty())
    {
        std::cout << "Stopping video: " << currentPlayingVideo.getTitle() << std::endl;
        currentPlayingVideo = Video("", "", { "" }); //Resets currentPlayingVideo variable
    }
    else //Display error since no video is playing
    {
        std::cout << "Cannot stop video: No video is currently playing" << std::endl;
    }
}

void VideoPlayer::playRandomVideo() 
{
    //Initialise vector of all available videos
    std::vector<Video> videos = mVideoLibrary.getVideos();

    //Play a random video
    playVideo(videos[rand() % videos.size()].getVideoId());
}

void VideoPlayer::pauseVideo() 
{
    //If a video is currently playing, pause it
    if (!currentPlayingVideo.getTitle().empty())
    {
        if (paused) //Check if the video is already paused
        {
            std::cout << "Video already paused: " << currentPlayingVideo.getTitle() << std::endl;
        }
        else 
        {
            paused = true;
            std::cout << "Pausing video: " << currentPlayingVideo.getTitle() << std::endl;
        }
    }
    else 
    { //Unable to pause video since no video is playing
        std::cout << "Cannot pause video: No video is currently playing" << std::endl;
    }
}

void VideoPlayer::continueVideo() {
    //Check if a video is currently being played
    if (!currentPlayingVideo.getTitle().empty())
    {
        if (paused) //Check if the video is paused, if so then disable pause
        {
            std::cout << "Continuing video: " << currentPlayingVideo.getTitle() << std::endl;
            paused = false;
        }
        else
        {
            std::cout << "Cannot continue video: Video is not paused" << std::endl;
        }
    }
    else
    { //Unable to continue video since no video is playing
        std::cout << "Cannot continue video: No video is currently playing" << std::endl;
    }
}

void VideoPlayer::showPlaying() {
    //Check if a video is currently being played
    if (!currentPlayingVideo.getTitle().empty())
    {
        std::string hashtags = "";
        for (const std::string tag : currentPlayingVideo.getTags())
        {
            hashtags += tag + " ";
        }

        if (hashtags.size() > 0) { hashtags.resize(hashtags.size() - 1); }
        
        std::string displayString = "Currently playing: " + currentPlayingVideo.getTitle() + " (" + currentPlayingVideo.getVideoId() + ") [" + hashtags + "]";
        if (paused) { displayString += " - PAUSED"; }
        std::cout << displayString << std::endl;
    }
    else
    { //Unable to display video info since no video is playing
        std::cout << "No video is currently playing" << std::endl;
    }
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  std::cout << "createPlaylist needs implementation" << std::endl;
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "addVideoToPlaylist needs implementation" << std::endl;
}

void VideoPlayer::showAllPlaylists() {
  std::cout << "showAllPlaylists needs implementation" << std::endl;
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  std::cout << "showPlaylist needs implementation" << std::endl;
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "removeFromPlaylist needs implementation" << std::endl;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  std::cout << "deletePlaylist needs implementation" << std::endl;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
    //Initialises vector of all videos in the library
    std::vector<Video> videos = mVideoLibrary.getVideos();
    //Initialises the number of videos available
    int vectorSize = mVideoLibrary.getVideos().size();

    //Creates a vector of video names
    std::vector<std::string> videoNames(vectorSize);
    for (size_t i = 0; i < vectorSize; i++)
    {
        videoNames[i] = videos[i].getTitle();
    }

    //Sorts the list of video names into lexicographical order
    std::sort(videoNames.begin(), videoNames.end(), comparator);

    int videosFound = 0;
    //For loop in lexicographical order, displaying video information
    for (std::string videoName : videoNames)
    {
        for (Video video : videos)
        {//Check if search term is within video title

            std::string videoTitle = video.getTitle();

            if (videoTitle == videoName && toUpper(videoTitle).find(toUpper(searchTerm)) != std::string::npos)
            {
                if(videosFound == 0) { std::cout << "Here are the results for " << searchTerm << ":" << std::endl; }
                videosFound++;
                std::string hashtags = "";
                for (const std::string tag : video.getTags())
                {
                    hashtags += tag + " ";
                }

                if (hashtags.size() > 0) { hashtags.resize(hashtags.size() - 1); }
                std::cout << videosFound << ") " << video.getTitle() << " (" << video.getVideoId() << ") [" << hashtags << "]" << std::endl;
            }
        }
    }

    if(videosFound == 0) 
    {
        std::cout << "No search results for " << searchTerm << std::endl;
    }
    else 
    {
        std::cout << "Would you like to play any of the above? If yes, specify the number of the video." << std::endl;
        std::cout << "If your answer is not a valid number, we will assume it's a no." << std::endl;

        std::string userInput;
        std::cin >> userInput;

        int userChoice;
        try {
            userChoice = std::stoi(userInput);
        }
        catch (...) {
            return;
        }
        
        if (userChoice > 0 && userChoice <= videosFound) {
            int index = 0;
            //For loop in lexicographical order, displaying video information
            for (std::string videoName : videoNames)
            {
                for (Video video : videos)
                {//Check if search term is within video title
                    std::string videoTitle = video.getTitle();

                    if (videoTitle == videoName && toUpper(videoTitle).find(toUpper(searchTerm)) != std::string::npos)
                    {
                        index++;
                        if (index == userChoice) {
                            playVideo(video.getVideoId());
                        }
                    }
                }
            }
        }
    }
}

std::string VideoPlayer::toUpper(std::string str) {
    for (int x = 0; x < str.length(); x++)
        str[x] = toupper(str[x]);

    return str;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
    //Initialises vector of all videos in the library
    std::vector<Video> videos = mVideoLibrary.getVideos();
    //Initialises the number of videos available
    int vectorSize = mVideoLibrary.getVideos().size();

    //Creates a vector of video names
    std::vector<std::string> videoNames(vectorSize);
    for (size_t i = 0; i < vectorSize; i++)
    {
        videoNames[i] = videos[i].getTitle();
    }
    bool tagMatched = false;
    //Sorts the list of video names into lexicographical order
    std::sort(videoNames.begin(), videoNames.end(), comparator);

    int videosFound = 0;
    //For loop in lexicographical order, displaying video information
    for (std::string videoName : videoNames)
    {
        for (Video video : videos)
        {//Check if input hashtag matches with video hashtags

            std::string videoTitle = video.getTitle();

            if (videoTitle == videoName)
            {
                tagMatched = false;

                for (const std::string tag : video.getTags())
                {
                    if (toUpper(tag) == toUpper(videoTag)) { tagMatched = true; }
                }

                if (tagMatched)
                {
                    if (videosFound == 0) { std::cout << "Here are the results for " << videoTag << ":" << std::endl; }
                    videosFound++;
                    std::string hashtags = "";
                    for (const std::string tag : video.getTags())
                    {
                        hashtags += tag + " ";
                    }

                    if (hashtags.size() > 0) { hashtags.resize(hashtags.size() - 1); }
                    std::cout << videosFound << ") " << video.getTitle() << " (" << video.getVideoId() << ") [" << hashtags << "]" << std::endl;
                }
  
            }
        }
    }

    if (!tagMatched) {
        std::cout << "No search results for " << videoTag << std::endl;
    }
    else 
    {
        std::cout << "Would you like to play any of the above? If yes, specify the number of the video." << std::endl;
        std::cout << "If your answer is not a valid number, we will assume it's a no." << std::endl;

        std::string userInput;
        std::cin >> userInput;

        int userChoice;
        try {
            userChoice = std::stoi(userInput);
        }
        catch (...) {
            return;
        }

        if (userChoice > 0 && userChoice <= videosFound) {
            int index = 0;
            //For loop in lexicographical order, displaying video information
            for (std::string videoName : videoNames)
            {
                for (Video video : videos)
                {//Check if search term is within video title
                    std::string videoTitle = video.getTitle();

                    if (videoTitle == videoName)
                    {
                        bool tagMatched = false;
                        for (const std::string tag : video.getTags())
                        {
                            if (toUpper(tag) == toUpper(videoTag)) { tagMatched = true; }
                        }

                        if (tagMatched) {
                            index++;
                            if (index == userChoice) {
                                playVideo(video.getVideoId());
                            }
                        }
                    }
                }
            }
        }
    }
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
