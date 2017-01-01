#!/bin/bash

set -ev

openssl aes-256-cbc -K $encrypted_482e2f17cfc1_key -iv $encrypted_482e2f17cfc1_iv -in credentials.tar.gz.enc -out credentials.tar.gz -d;
if [ ! -d ${HOME}/google-cloud-sdk ]; then curl https://sdk.cloud.google.com | bash ; fi ;
tar -xzf credentials.tar.gz;
gcloud auth activate-service-account --key-file RType-server-736393d1bca7.json;

gcloud config set project rtype-server;
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet;
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet --command="git clone -b ${TRAVIS_BRANCH} https://github.com/HippoBaro/R-Type.git";
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet --command="bash R-Type/install_run_server.sh";

exit 0;