## drone-ci docker jizz

To rebuild all ci images and push them to the beldex registry server do:

    $ docker login registry.beldex.rocks
    $ ./rebuild-docker-images.py

If you aren't part of the Beldex team, you'll likely need to set up your own registry and change
registry.beldex.rocks to your own domain name in order to do anything useful with this.
