import slowclap as sc
feed = sc.MicrophoneFeed()
detector = sc.AmplitudeDetector(feed, threshold=17000000)
for clap in detector:
    # do something
    print(clap.time)