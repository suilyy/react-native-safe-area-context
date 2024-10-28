// @ts-check
const { execSync } = require('child_process');
const fs = require('node:fs');
const readline = require('readline');
const fetch = require('node-fetch');

const RNOH_REPO_TOKEN = process.env.RNOH_REPO_TOKEN ?? '';

if (!RNOH_REPO_TOKEN) {
  console.log('RNOH_REPO_TOKEN not found');
  process.exit(1);
}

const EXPECTED_EXECUTION_DIRECTORY_NAME = 'react-native-safe-area-context';
const GITHUB_URL = 'https://api.github.com';
// const OWNER = 'react-native-oh-library';
const OWNER = 'suilyy';
const MODULE_NAME = 'safe_area';
let HAR_FILE_OUTPUT_PATH = `/harmony/${MODULE_NAME}/build/default/outputs/default/${MODULE_NAME}.har`;
const UNSCOPED_NPM_PACKAGE_NAME = 'react-native-safe-area-context';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

function runDeployment() {
  // if (!process.cwd().endsWith(EXPECTED_EXECUTION_DIRECTORY_NAME)) {
  //   console.log(
  //     `This script should be executed from ${EXPECTED_EXECUTION_DIRECTORY_NAME} directory`
  //   );
  //   process.exit(1);
  // }

  // if (!isRepositoryClean()) {
  //   console.log(
  //     'Repository should be clean, on sig branch and up to date with upstream.'
  //   );
  //   process.exit(1);
  // }

  let version = '',tester="";

  const currentVersion = JSON.parse(
    fs.readFileSync('./package.json').toString()
  )['version'];
  rl.question(
    `A complete tester path be like: D://Code/Project/tester. Enter your tester path: `,
    (newTester) => {
      tester = newTester;
      HAR_FILE_OUTPUT_PATH = tester + HAR_FILE_OUTPUT_PATH
      rl.question(
        `Current version: ${currentVersion}. Enter new version: `,
        (newVersion) => {
          version = newVersion;
    
          execSync(`npm run update_version  -- --new-version ${version} --tester-path ${tester}`, {
            stdio: 'inherit',
          });
    
          rl.question(
            `Please generate ${HAR_FILE_OUTPUT_PATH} file. Open DevEco Studio, select any file in '${MODULE_NAME}' module, and run Build > Make Module '${MODULE_NAME}'.\nOnce you finish type 'done': `,
            (answer) => {
              if (answer !== 'done') {
                console.log('Deployment aborted');
                process.exit(1);
              }
              console.log(
                `Copying ${`${HAR_FILE_OUTPUT_PATH}`} to ./harmony dir`
              );
              if (!fs.existsSync(`${HAR_FILE_OUTPUT_PATH}`)) {
                console.log(`Couldn't find ${HAR_FILE_OUTPUT_PATH}.`);
                process.exit(1);
              }
              if(!fs.existsSync('./harmony')){
                fs.mkdirSync('./harmony');
              }
              // fs.rmSync('./harmony', { recursive: true, force: true });
              // fs.mkdirSync('./harmony');
              fs.renameSync(
                `${HAR_FILE_OUTPUT_PATH}`,
                `./harmony/${MODULE_NAME}.har`
              );
              
    
              // const changelogForCurrentVersion = execSync(
              //   `npm run -s gen:changelog`
              // ).toString();
              // updateChangelog(version, changelogForCurrentVersion);
    
              // execSync(`npm publish --dry-run`, { stdio: 'inherit' });
    
              rl.question(
                'Are changes good to be published and pushed to the upstream? (yes/no): ',
                async (answer) => {
                  if (answer.toLowerCase() === 'yes') {
                    // execSync(`npm publish`, { stdio: 'inherit' });
                    // console.log('NPM Package was published successfully.');
                    execSync(
                      `git checkout -b release-${UNSCOPED_NPM_PACKAGE_NAME}-${version}`
                    );
                    execSync('git add -A');
                    execSync(
                      `git commit -m "release: ${UNSCOPED_NPM_PACKAGE_NAME}@${version}"`,
                      {
                        stdio: 'inherit',
                      }
                    );
                    execSync(`git push -u origin HEAD --no-verify`, {
                      stdio: 'inherit',
                    });
    
                    execSync(`git tag v${version}`);
                    execSync(`git push -u origin v${version} --no-verify`, {
                      stdio: 'inherit',
                    });
                    const merge_Request_html_url = await createMergeRequest(
                      `release-${UNSCOPED_NPM_PACKAGE_NAME}-${version}`,
                      `release: ${UNSCOPED_NPM_PACKAGE_NAME}@${version}`
                    );
                    console.log(`Please merge the following Merge Request:\n${merge_Request_html_url}`);
                    rl.close();
                  } else {
                    console.log('Deployment aborted.');
                    rl.close();
                  }
                }
              );
            }
          );
        }
      );
    }
  );
}

/**
 * @returns {boolean}
 */
function isRepositoryClean() {
  const status = execSync('git status --porcelain', { encoding: 'utf-8' });
  const branch = execSync('git branch --show-current', {
    encoding: 'utf-8',
  }).trim();
  const isUpdated =
    execSync('git rev-list HEAD...origin/sig --count', {
      encoding: 'utf-8',
    }).trim() === '0';
    console.log(!status , branch === 'sig' , isUpdated,!status && branch === 'sig' && isUpdated
    );
  return !status && branch === 'sig' && isUpdated;
}

/**
 * @param {string} version
 *  @param {string} changelogForCurrentVersion
 */
function updateChangelog(version, changelogForCurrentVersion) {
  let data = fs.readFileSync('../CHANGELOG.md').toString();
  data = data.replace(
    '# Changelog',
    `# Changelog\n\n## v${version}\n ${changelogForCurrentVersion}`
  );
  fs.writeFileSync('../CHANGELOG.md', data);
}

/**
 * @param {string} sourceBranch
 * @param {string} title
 * @returns {Promise<number>}
 */
async function createMergeRequest(sourceBranch, title) {
  try {
    const response = await fetch(
      `${GITHUB_URL}/repos/${OWNER}/${UNSCOPED_NPM_PACKAGE_NAME}/pulls`,
      {
        method: 'POST',
        headers: {
          'Authorization': `token ${RNOH_REPO_TOKEN}`,
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          title: title,
          'head': `${sourceBranch}`, // fork仓库分支
          'base': `sig` // 源仓库分支
        }),
      }
    );
    if (!response.ok) {
      throw new Error(
        `Failed to create merge request: ${response.statusText} ${response.status}`
      );
    }
    const responseData = await response.json();
    // console.log(JSON.stringify(responseData))
    return responseData.html_url;
  } catch (error) {
    console.error('Error creating merge request:', error);
    throw error;
  }
}

runDeployment();
