#!/bin/bash

set -ev

openssl aes-256-cbc -K $encrypted_482e2f17cfc1_key -iv $encrypted_482e2f17cfc1_iv -in credentials.tar.gz.enc -out credentials.tar.gz -d;
tar -xzf credentials.tar.gz;

gcloud version || true
if [ ! -d "$HOME/google-cloud-sdk/bin" ]; then rm -rf $HOME/google-cloud-sdk; export CLOUDSDK_CORE_DISABLE_PROMPTS=1; curl https://sdk.cloud.google.com | bash > /dev/null; fi
source /home/travis/google-cloud-sdk/path.bash.inc
gcloud version
gcloud auth activate-service-account --key-file RType-server-736393d1bca7.json;

gcloud config set project rtype-server;
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet --command="rm -rf R-Type";
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet --command="git clone -b ${TRAVIS_BRANCH} https://github.com/HippoBaro/R-Type.git";
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet --command="bash R-Type/install_run_server.sh";
gcloud compute --project "rtype-server" ssh --zone "europe-west1-c" "rtype-server-dev" --quiet --command="./R-Type/build/BUILD/R_Type_Server &";

exit 0;