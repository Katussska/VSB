#include <string>
#include <iostream>
#include <vector>

class Media
{
private:
    int id;
    std::string title;

public:
    Media(int id, std::string title)
    {
        this->id = id;
        this->title = title;
    }

    virtual std::string getType() = 0; // virtual
};

class DVD : public Media
{
private:
    std::string duration;

public:
    DVD(int id, std::string title, std::string duration)
        : Media(id, title)
    {
        this->duration = duration;
    }

    void setDuration(std::string duration)
    {
        this->duration = duration;
    }

    std::string getType()
    {
        return "DVD";
    }

    std::string getDuration()
    {
        return duration;
    }
};

class CD : public DVD
{
private:
    int numOfTracks;

public:
    CD(int id, std::string title, int numberOfTracks, std::string duration)
        : DVD(id, title, duration)
    {
        this->numOfTracks = numberOfTracks;
    }

    void setNumOfTracks(int number)
    {
        this->numOfTracks = number;
    }

    std::string getType()
    {
        return "CD";
    }

    int getNumOfTracks()
    {
        return numOfTracks;
    }
};

class BluRay : public Media // abstract class
{
private:
    std::string videoCodec;
    std::string audioCodec;

public:
    BluRay(int id, std::string title, std::string videoCodec, std::string audioCodec)
        : Media(id, title)
    {
        this->videoCodec = videoCodec;
        this->audioCodec = audioCodec;
    }

    virtual std::string getType() override
    {
        return "Blu-ray";
    }

    void setVideoCodec(std::string codec)
    {
        this->videoCodec = codec;
    }

    void setAudioCodec(std::string codec)
    {
        this->audioCodec = codec;
    }

    std::string getVideoCodec()
    {
        return videoCodec;
    }

    std::string getAudioCodec()
    {
        return audioCodec;
    }

    virtual ~BluRay() {}
};