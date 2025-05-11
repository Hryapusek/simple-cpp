#include <memory>
#include <stdexcept>
#include <array>

struct skcipher_def
{
  std::unique_ptr<struct crypto_skcipher, decltype(&crypto_free_skcipher)> tfm;
  std::unique_ptr<struct skcipher_request, decltype(&skcipher_request_free)> req;
  struct crypto_wait wait;
  std::array<unsigned char, 32> key;
  std::unique_ptr<char[]> ivdata;
  std::unique_ptr<char[]> scratchpad;
};

/* Perform cipher operation */
static unsigned int test_skcipher_encdec(skcipher_def& sk, int enc)
{
  int rc;

  if(enc)
    rc = crypto_wait_req(crypto_skcipher_encrypt(sk.req.get()), &sk.wait);
  else
    rc = crypto_wait_req(crypto_skcipher_decrypt(sk.req.get()), &sk.wait);

  if(rc)
    throw std::runtime_error("skcipher encrypt returned with result " + std::to_string(rc));

  return rc;
}

/* Initialize and trigger cipher operation */
static int test_skcipher()
{
  try {
    skcipher_def sk;
    sk.tfm = std::unique_ptr<struct crypto_skcipher, decltype(&crypto_free_skcipher)>(
      crypto_alloc_skcipher("cbc-aes-aesni", 0, 0)
    );
    if(! sk.tfm)
      throw std::runtime_error("could not allocate skcipher handle");

    sk.req = std::unique_ptr<struct skcipher_request, decltype(&skcipher_request_free)>(
      skcipher_request_alloc(sk.tfm.get(), GFP_KERNEL)
    );
    if(! sk.req)
      throw std::runtime_error("could not allocate skcipher request");

    skcipher_request_set_callback(
      sk.req.get(),
      CRYPTO_TFM_REQ_MAY_BACKLOG,
      crypto_req_done,
      &sk.wait
    );

    /* AES 256 with random key */
    get_random_bytes(&sk.key, 32);
    if(crypto_skcipher_setkey(sk.tfm.get(), sk.key.data(), 32))
      throw std::runtime_error("key could not be set");

    /* IV will be random */
    sk.ivdata = std::make_unique<char[]>(16);
    get_random_bytes(sk.ivdata.get(), 16);

    /* Input data will be random */
    sk.scratchpad = std::make_unique<char[]>(16);
    get_random_bytes(sk.scratchpad.get(), 16);

    /* We encrypt one block */
    struct scatterlist sg;
    sg_init_one(&sg, sk.scratchpad.get(), 16);
    skcipher_request_set_crypt(sk.req.get(), &sg, &sg, 16, sk.ivdata.get());
    crypto_init_wait(&sk.wait);

    /* encrypt data */
    test_skcipher_encdec(sk, 1);

    std::cout << "Encryption triggered successfully\n";
  } catch(std::exception const& e) {
    std::cerr << e.what() << '\n';
    return -EAGAIN;
  }

  return 0;
}
